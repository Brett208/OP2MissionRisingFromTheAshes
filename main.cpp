#include "AIFightGroups.h"
#include "Disasters.h"
#include "UnitHelper.h"
#include "MapHelper.h"
#include "PlayerBaseBuilder.h"
#include "AIHelper.h"
#include "PlayList.h"
#include "ScriptGlobal.h"

#include "OP2Helper\OP2Helper.h"
#include "Outpost2DLL\Outpost2DLL.h" 

#include <vector> 

// Declaring Classes
UnitHelper::VehicleBuilder vehicleBuilderAI;
AIFightGroups::AIFightGroupMaker fightGroupMaker;
ScriptGlobal scriptGlobal;

ExportLevelDetails("Colony Builder - Eden, Rising From the Ashes", "Ashes.map", "multitekNoLavaWalls.txt", MissionTypes::Colony, 2)
ExportSaveLoadData(scriptGlobal);

std::vector<map_id> aiBuildingRepairOrder{ map_id::mapCommandCenter, map_id::mapStructureFactory,
	map_id::mapVehicleFactory, map_id::mapTokamak, map_id::mapRareOreMine, map_id::mapCommonOreMine,
	map_id::mapRareOreSmelter, map_id::mapCommonOreSmelter,map_id::mapAgridome,  map_id::mapCommonStorage,
	map_id::mapRareStorage,  map_id::mapUniversity, map_id::mapNursery, map_id::mapRobotCommand,
	map_id::mapResidence, map_id::mapGuardPost };

LOCATION volcanoEruptionLoc = LOCATION(50 + X_, 125 + Y_);

//Forward declaring functions
extern void ShowBriefing();
void BuildEnemyBase(UnitHelper::VehicleBuilder vehicleBuilderAI, LOCATION commonBeaconLoc, LOCATION rareBeaconLoc);

// Function Declarations
void CreateFumaroles();
void CreateMineBeacons(LOCATION &aiCommonBeaconLoc, LOCATION &aiRareBeaconLoc);
void InitializeVolcano(LOCATION lavaFlowStartLoc);
void InitializeRandomAttackTrigger();
void InitializeDisasterTrigger();
void InitializeAIHelperClasses();
void InitializeVictoryConditions();
void UpdateAIRepairs();
void CheckOnTriggeringBaseReinforcements();
bool CheckIfGameFailed();
void UpdateAIVehicleFactory();
void RetreatAINonCombatantsSouth(int southernYCoordOfEnemyCombatant);

/**
 * Called once when level is first initialized.
 * 
 * This is where you're going to put your initial units, structures and define
 * environment settings such as day and night.
 */
int InitProc()
{
	HFLInit();
	
	ShowBriefing();

	InitializeVolcano(volcanoEruptionLoc);
	
	Player[0].GoEden();
	Player[0].SetColorNumber(PlayerColor::PlayerBlue);

	Player[1].GoPlymouth();
	Player[1].SetColorNumber(PlayerColor::PlayerRed);
	Player[1].GoAI();
	TethysGame::ForceMoraleGood(1);
	InitializeAIHelperClasses();

	LOCATION aiCommonBeaconLoc;
	LOCATION aiRareBeaconLoc;

	CreateMineBeacons(aiCommonBeaconLoc, aiRareBeaconLoc);
	CreateFumaroles();

	BuildPlayerBase();
	BuildEnemyBase(vehicleBuilderAI, aiCommonBeaconLoc, aiRareBeaconLoc);
	
	fightGroupMaker.SetupBaseDefenseFightGroup(scriptGlobal.BaseDefenseFightGroup);
	scriptGlobal.ReinforceVehicleBuildGroup.RecordVehReinforceGroup(scriptGlobal.BaseDefenseFightGroup, 1);

	TethysGame::SetDaylightEverywhere(0);
	TethysGame::SetDaylightMoves(1);
	GameMap::SetInitialLightLevel(TethysGame::GetRand(64));

	InitializeDisasterTrigger();
	InitializeVictoryConditions();

	// Failure Conditions
	scriptGlobal.TrigFailureWaitTime = CreateTimeTrigger(0, 0, 90, "NoResponseToTrigger");
	CreateFailureCondition(1, 0, scriptGlobal.TrigFailureWaitTime, "Ignored");

	InitializeRandomAttackTrigger();
	
	scriptGlobal.TrigRareMineDestroyed = CreateTimeTrigger(false, true, 1000 + TethysGame::GetRand(1200), "SendRareOreFightGroup");
	scriptGlobal.TrigSpaceportBuilt = CreateTimeTrigger(false, true, 1000 + TethysGame::GetRand(800), "SendSpaceportFightGroup");
	scriptGlobal.TrigPhoenixModuleResearched = CreateTimeTrigger(false, true, 1000 + TethysGame::GetRand(1200), "SendPhoenixModuleFightGroup");
	
	scriptGlobal.TrigAIBaseReinforcement = CreateTimeTrigger(false, true, 1000 + TethysGame::GetRand(1200), "AddRepairConVec");

	TethysGame::SetMusicPlayList(7, 1, PlayList);

	return 1;
}

Export void AIProc()
{
	//Ensure random stealth attacks turn on lights when attacked.
	if (scriptGlobal.PeriodicFightGroup.IsInitialized() &&
		scriptGlobal.PeriodicFightGroup.HasBeenAttacked())
	{
		scriptGlobal.PeriodicFightGroup.SetLights(true);
	}

	//NOTE: When the VehicleBuilder class is instantiated after a game is loaded, it defaults to player 0.
	if (vehicleBuilderAI.GetPlayer() != Player1)
	{
		InitializeAIHelperClasses();
	}

	int southernYCoordOfEnemyCombatant = UnitHelper::FindSouthernYCoordOfCombatant(0);
	RetreatAINonCombatantsSouth(southernYCoordOfEnemyCombatant);

	UpdateAIVehicleFactory();
	UpdateAIRepairs();

	//Note: This attack is meant for after rare ore mine is destroyed, however to keep
	//      gaming the scenario down a little, destroying the command center or struct factor also trigger attack.
	if ((!UnitHelper::BuildingConstructed(Player1, map_id::mapRareOreMine) || 
		!UnitHelper::BuildingConstructed(Player1, map_id::mapCommandCenter) || 
		!UnitHelper::BuildingConstructed(Player1, map_id::mapStructureFactory)) &&
		!scriptGlobal.TrigRareMineDestroyed.HasFired(Player1))
	{
		scriptGlobal.TrigRareMineDestroyed.Enable();
	}

	if ((UnitHelper::BuildingConstructed(Player0, mapSpaceport) || 
		(Player[0].Difficulty() == PlayerDifficulty::DiffHard && TethysGame::Tick() / 100 > 1150)) && 
		!scriptGlobal.TrigSpaceportBuilt.HasFired(Player0))
	{
		scriptGlobal.TrigSpaceportBuilt.Enable();
	}

	if (Player[0].HasTechnology(10401) && 
		!scriptGlobal.TrigPhoenixModuleResearched.HasFired(Player0))
	{
		scriptGlobal.TrigPhoenixModuleResearched.Enable();
	}

	if (CheckIfGameFailed())
	{
		scriptGlobal.TrigFailureWaitTime.Enable();
	}
}

void InitializeVolcano(LOCATION lavaFlowStartLoc)
{
	int marksToErupt = 1350;

	if (Player[0].Difficulty() == PlayerDifficulty::DiffEasy)
	{
		marksToErupt += 250;
	}
	else if (Player[0].Difficulty() == PlayerDifficulty::DiffNormal)
	{
		marksToErupt += 125;
	}

	scriptGlobal.TrigVolcanoEruption = CreateTimeTrigger(true, true, marksToErupt * 100, "VolcanoErupts");
	//scriptGlobal.TrigVolcanoEruption = CreateTimeTrigger(true, true, 10, "VolcanoErupts");

	MapHelper::SetLavaPossibleRegion(MAP_RECT(LOCATION(50 + X_, 125 + Y_), LOCATION(51 + X_, 131 + Y_)));
	MapHelper::SetLavaPossibleAllSlowCells(MAP_RECT(LOCATION(0 + X_, 0 + Y_), LOCATION(64 + X_, 256 + Y_)));

	MapHelper::SetSouthEastLavaFlowAni(lavaFlowStartLoc);
}

void CheckIfAIVehicleFactoryDestroyed()
{
	UnitEx structure;
	PlayerBuildingEnum findStructures(Player1, map_id::mapVehicleFactory);

	scriptGlobal.AIVehicleFactoryDestoryed = true;
	while (findStructures.GetNext(structure))
	{
		scriptGlobal.AIVehicleFactoryDestoryed = false;
		break;
	}
}

/**
* Note: This function will not allow restoring the vehicle factory to it's associated buildingGroups if it is damage while being rebuilt.
*/
void UpdateDestroyedAIVehicleFactory()
{
	UnitEx structure;
	PlayerBuildingEnum findStructures(Player1, map_id::mapVehicleFactory);

	while (findStructures.GetNext(structure))
	{
		if (scriptGlobal.AIRepairConvec.GetCurAction() == ActionType::moDone ||
			scriptGlobal.AIRepairConvec.GetCurAction() == ActionType::moInvalid)
		{
			AIHelper::SearchForBuildingToRepair(scriptGlobal.AIRepairConvec, Player1, 1, map_id::mapVehicleFactory);
		}

		if (structure.GetDamage() != 0)
		{
			break;
		}

		scriptGlobal.ReinforceVehicleBuildGroup.TakeUnit(structure);
		scriptGlobal.ColonyExpansionBuildGroup.TakeUnit(structure);
		scriptGlobal.AIVehicleFactoryDestoryed = false;
		break;
	}
}

void UpdateAIVehicleFactory()
{
	if (scriptGlobal.AIVehicleFactoryDestoryed)
	{
		UpdateDestroyedAIVehicleFactory();
	}
	else
	{
		CheckIfAIVehicleFactoryDestroyed();
	}
}

void RetreatAINonCombatantsSouth(int southernYCoordOfEnemyCombatant)
{
	UnitEx unit;
	PlayerVehicleEnum vehicleEnum(Player1);

	while (vehicleEnum.GetNext(unit))
	{
		//NOTE: This prevents a player from camping out close to the guard posts and forcing either the expansion conVec or the Earthworker to continuosly retreat.
		if ((unit.GetType() == map_id::mapConVec && unit.GetCargo() != map_id::mapGuardPost) ||
			unit.GetType() == map_id::mapRoboMiner ||
			unit.GetType() == map_id::mapCargoTruck)
		{
			if (unit.Location().y < southernYCoordOfEnemyCombatant + 8)
			{
				LOCATION aiRetreatLoc = LOCATION(33 + X_, 210 + Y_);
				unit.DoMove(aiRetreatLoc);
			}
		}
	}
}

void SetRepairOrderIfRepairVehicleIdle(UnitEx &repairVehicle)
{
	if (repairVehicle.GetCurAction() == ActionType::moDone ||
		repairVehicle.GetCurAction() == ActionType::moInvalid)
	{
		AIHelper::SearchForBuildingToRepair(repairVehicle, 1, 100, aiBuildingRepairOrder);
	}
}

void InitializeDisasterTrigger()
{
	int disasterTimeMin = 2500;
	int disasterTimeMax = 6500;

	if (Player[0].Difficulty() == PlayerDifficulty::DiffNormal)
	{
		disasterTimeMin = 2000;
		disasterTimeMax = 6000;
	}
	else if (Player[0].Difficulty() == PlayerDifficulty::DiffHard)
	{
		disasterTimeMin = 1500;
		disasterTimeMax = 5500;
	}

	scriptGlobal.TrigDisaster = CreateTimeTrigger(true, false, disasterTimeMin, disasterTimeMax, "InitializeRandomDisaster");
}

void InitializeRandomAttackTrigger()
{
	int attackTimeMin = 5000;
	int attackTimeMax = 8000;

	if (Player[0].Difficulty() == PlayerDifficulty::DiffNormal)
	{
		attackTimeMin = 3000;
		attackTimeMax = 5500;
	}
	else if (Player[1].Difficulty() == PlayerDifficulty::DiffHard)
	{
		attackTimeMin = 2000;
		attackTimeMax = 4000;
	}

	scriptGlobal.TrigRandomFightGroup = CreateTimeTrigger(false, false, attackTimeMin, attackTimeMax, "SendRandomFightGroup");
}

void InitializeAIHelperClasses()
{
	vehicleBuilderAI.SetPlayer(Player1);
	fightGroupMaker.VehicleBuilderAI = vehicleBuilderAI;
}

void CreateFumaroles()
{
	MapHelper::CreateFumaroleInRegion(MAP_RECT(LOCATION(36 + X_, 15 + Y_), LOCATION(42 + X_, 19 + Y_)));
	MapHelper::CreateFumaroleInRegion(MAP_RECT(LOCATION(42 + X_, 111 + Y_), LOCATION(63 + X_, 118 + Y_)));
	MapHelper::CreateFumaroleInRegion(MAP_RECT(LOCATION(44 + X_, 132 + Y_), LOCATION(63 + X_, 139 + Y_)));

	std::vector<LOCATION> possFumaroleLocs{
		LOCATION(45 + X_, 87 + Y_),
		LOCATION(51 + X_, 77 + Y_),
		LOCATION(38 + X_, 71 + Y_),
		LOCATION(54 + X_, 89 + Y_),
		LOCATION(41 + X_, 80 + Y_) };

	MapHelper::CreateFumarolesFromRandomLocs(1, possFumaroleLocs);
}

void CreateMineBeacons(LOCATION &aiCommonBeaconLoc, LOCATION &aiRareBeaconLoc)
{
	MAP_RECT mapRect = MAP_RECT(LOCATION(36 + X_, 62 + Y_), LOCATION(49 + X_, 68 + Y_));
	LOCATION playerCommonBeaconLoc = mapRect.RandPt();

	TethysGame::CreateBeacon(mapMiningBeacon, playerCommonBeaconLoc.x, playerCommonBeaconLoc.y,
		BeaconTypes::OreTypeCommon, Yield::Bar2, Variant::Variant1);

	mapRect = MAP_RECT(LOCATION(38 + X_, 172 + Y_), LOCATION(63 + X_, 176 + Y_));
	aiRareBeaconLoc = mapRect.RandPt();
	aiCommonBeaconLoc = aiRareBeaconLoc;

	while (DistanceBetweenPoints(aiCommonBeaconLoc, aiRareBeaconLoc) < 4)
	{
		aiCommonBeaconLoc = mapRect.RandPt();
	}

	TethysGame::CreateBeacon(mapMiningBeacon, aiCommonBeaconLoc.x, aiCommonBeaconLoc.y,
		BeaconTypes::OreTypeCommon, Yield::Bar1, Variant::Variant2);
	TethysGame::CreateBeacon(mapMiningBeacon, aiRareBeaconLoc.x, aiRareBeaconLoc.y,
		BeaconTypes::OreTypeRare, Yield::Bar1, Variant::Variant1);
}

void InitializeVictoryConditions()
{
	// Evacuation Module
	scriptGlobal.TrigVictoryColonists = CreateCountTrigger(true, true, Player0, mapEvacuationModule, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, true, scriptGlobal.TrigVictoryColonists, "Evacuate 200 colonists to the starship.");

	// Rare Metals Cargo
	scriptGlobal.TrigVictoryRareMetals = CreateCountTrigger(true, true, Player0, mapRareMetalsCargo, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, true, scriptGlobal.TrigVictoryRareMetals, "Evacuate 10000 units of Rare Metals to the starship.");

	// Common Metals Cargo
	scriptGlobal.TrigVictoryCommonMetals = CreateCountTrigger(true, true, Player0, mapCommonMetalsCargo, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, true, scriptGlobal.TrigVictoryCommonMetals, "Evacuate 10000 units of Common Metals to the starship.");

	// Food Cargo
	scriptGlobal.TrigVictoryFood = CreateCountTrigger(true, true, Player0, mapFoodCargo, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, true, scriptGlobal.TrigVictoryFood, "Evacuate 10000 units of food to the starship.");

	// Skydock
	scriptGlobal.TrigVictorySkydock = CreateCountTrigger(true, true, Player0, mapSkydock, mapNone, 1, cmpGreaterEqual, "NoResponseToTrigger");
	CreateVictoryCondition(true, false, scriptGlobal.TrigVictorySkydock, "Launch the Skydock.");
}

void UpdateAIRepairs()
{
	Unit repairConvec;
	if (scriptGlobal.RepairGroup.GetFirstOfType(repairConvec, map_id::mapConVec, map_id::mapNone))
	{
		SetRepairOrderIfRepairVehicleIdle(scriptGlobal.AIRepairConvec);
	}
	else
	{
		CheckOnTriggeringBaseReinforcements();
	}
}

void CheckOnTriggeringBaseReinforcements()
{
	UnitEx repairConvec;
	if (scriptGlobal.ReinforceVehicleBuildGroup.TotalUnitCount() == 0 &&
		!scriptGlobal.RepairGroup.GetFirstOfType(repairConvec, map_id::mapConVec, map_id::mapNone) &&
		UnitHelper::BuildingConstructed(1, map_id::mapCommandCenter))
	{
		scriptGlobal.TrigAIBaseReinforcement.Enable();
	}
}

bool CheckIfGameFailed()
{
	Player[0].resetChecks();

	if (Player[0].Workers() < 8)
	{
		return true;
	}
	else if (Player[0].Scientists() < 3)
	{
		return true;
	}
	else if (!UnitHelper::BuildingOrKitAvailable(Player0, map_id::mapCommandCenter))
	{
	    return true;
	}
	else if (!Player[0].canBuildSpace())
	{
		return true;
	}
	// Technology 10401 = Phoenix Module.
	else if (!Player[0].HasTechnology(10401) && !Player[0].canDoResearch(10401))
	{
		return true;
	}

	return false;
}

Export void VolcanoErupts()
{
	TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 80);
	//TethysGame::SetEruption(volcanoEruptionLoc.x, volcanoEruptionLoc.y, 1000);
}

Export void SendRandomFightGroup()
{
	AIFightGroups::FightGroupLevel fightGroupLevel = AIFightGroups::FightGroupLevel::Initial;

	if (scriptGlobal.TrigPhoenixModuleResearched.HasFired(Player0))
	{
		fightGroupLevel = AIFightGroups::FightGroupLevel::End;
	}
	else if (scriptGlobal.TrigSpaceportBuilt.HasFired(Player0))
	{
		fightGroupLevel = AIFightGroups::FightGroupLevel::Middle;
	}

	fightGroupMaker.CreateRandomFightGroup(fightGroupLevel);
}

Export void SendRareOreFightGroup()
{
	fightGroupMaker.CreateRareOreMineAttack();
}

Export void SendSpaceportFightGroup()
{
	fightGroupMaker.CreateSpaceportAttack();
}

Export void SendPhoenixModuleFightGroup()
{
	fightGroupMaker.CreatePhoenixModuleAttack();
}

Export void InitializeRandomDisaster()
{
	std::vector<LOCATION> criticalBuildingLocations;

	UnitHelper::FindBuildingLocations(criticalBuildingLocations, Player0,
		std::vector<map_id> { map_id::mapCommandCenter, map_id::mapStructureFactory, map_id::mapCommonOreSmelter });
	UnitHelper::FindBuildingLocations(criticalBuildingLocations, Player1,
		std::vector<map_id> {map_id::mapCommandCenter, map_id::mapStructureFactory});

	CreateRandomDisaster(criticalBuildingLocations);
}

Export void AddRepairConVec()
{
	LOCATION startLoc = fightGroupMaker.GetRandSouthernVehicleStartLoc();

	UnitEx repairConvec;
	TethysGame::CreateUnit(repairConvec, map_id::mapConVec, startLoc, Player1, map_id::mapNone, UnitDirection::North);
	repairConvec.DoSetLights(true);

	scriptGlobal.AIRepairConvec = repairConvec;
	scriptGlobal.RepairGroup.TakeUnit(repairConvec);

	Unit roboMiner;
	vehicleBuilderAI.CreateVechLightsOn(roboMiner, map_id::mapRoboMiner, startLoc + LOCATION(1, 0), map_id::mapNone);
	scriptGlobal.ColonyExpansionBuildGroup.TakeUnit(roboMiner);

	std::vector<Unit> units;
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(2, 0), UnitDirection::East, 1, map_id::mapLynx, map_id::mapMicrowave, 3);

	for (Unit unit : units)
	{
		scriptGlobal.BaseDefenseFightGroup.TakeUnit(unit);
	}

	scriptGlobal.TrigAIBaseReinforcement.Disable();
}

/**
* Trigger callback function.
*
* This function is intentionally left empty and is used as the trigger callback
* function for triggers that don't want or need any special callback function.
*/
Export void NoResponseToTrigger() { }