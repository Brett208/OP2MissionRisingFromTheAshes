#include <vector>
#include "Outpost2DLL\Outpost2DLL.h"
#include "OP2Helper\OP2Helper.h"
#include "AIHelper.h"
#include "UnitHelper.h"
#include "ScriptGlobal.h"

extern ScriptGlobal scriptGlobal;

void SetupAIResources()
{
	Player[1].SetOre(24'500);
	Player[1].SetRareOre(2'000);
	Player[1].SetFoodStored(99'000);
	Player[1].SetKids(50);
	Player[1].SetWorkers(50);
	Player[1].SetScientists(20);
}

void SetupBuildGroup(Unit &earthworker, Unit &conVec, Unit &structFactory, Unit &vehicleFactory,
	std::vector<Unit> &buildingVector, MAP_RECT idleRect)
{
	BuildingGroup buildingGroup = CreateBuildingGroup(Player[1]);

	buildingGroup.TakeUnit(structFactory);
	buildingGroup.TakeUnit(vehicleFactory);
	buildingGroup.TakeUnit(earthworker);
	buildingGroup.TakeUnit(conVec);
	buildingGroup.SetRect(idleRect);

	for (Unit unit : buildingVector)
	{
		buildingGroup.RecordBuilding(unit.Location(), unit.GetType(), map_id::mapNone);
	}

	buildingGroup.RecordBuilding(LOCATION(4 + X_, 212 + Y_), map_id::mapTokamak, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(30 + X_, 192 + Y_), map_id::mapAgridome, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(36 + X_, 192 + Y_), map_id::mapUniversity, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(36 + X_, 195 + Y_), map_id::mapNursery, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(51 + X_, 164 + Y_), map_id::mapGuardPost, map_id::mapESG);
	buildingGroup.RecordBuilding(LOCATION(15 + X_, 167 + Y_), map_id::mapGuardPost, map_id::mapESG);
	buildingGroup.RecordBuilding(LOCATION(10 + X_, 167 + Y_), map_id::mapGuardPost, map_id::mapESG);
	buildingGroup.RecordBuilding(LOCATION(27 + X_, 164 + Y_), map_id::mapGuardPost, map_id::mapESG);
	buildingGroup.RecordBuilding(LOCATION(63 + X_, 169 + Y_), map_id::mapGuardPost, map_id::mapESG); //Far East Guard Post
	buildingGroup.RecordBuilding(LOCATION(35 + X_, 163 + Y_), map_id::mapGuardPost, map_id::mapESG);
	buildingGroup.RecordBuilding(LOCATION(44 + X_, 163 + Y_), map_id::mapGuardPost, map_id::mapESG);
	buildingGroup.RecordBuilding(LOCATION(25 + X_, 191 + Y_), map_id::mapResidence, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(22 + X_, 191 + Y_), map_id::mapResidence, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(27 + X_, 186 + Y_), map_id::mapRareStorage, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(25 + X_, 186 + Y_), map_id::mapRareStorage, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(23 + X_, 186 + Y_), map_id::mapRareStorage, map_id::mapNone);
	buildingGroup.RecordBuilding(LOCATION(23 + X_, 201 + Y_), map_id::mapRareStorage, map_id::mapNone);

	buildingGroup.RecordBuilding(LOCATION(36 + 31, 208 + Y_), map_id::mapRobotCommand, map_id::mapNone);

	buildingGroup.RecordBuilding(LOCATION(53 + X_, 170 + Y_), map_id::mapGuardPost, map_id::mapStickyfoam);
	buildingGroup.RecordBuilding(LOCATION(39 + X_, 166 + Y_), map_id::mapGuardPost, map_id::mapStickyfoam);
	buildingGroup.RecordBuilding(LOCATION(23 + X_, 168 + Y_), map_id::mapGuardPost, map_id::mapStickyfoam);

	//Tubes for Nursery and University
	buildingGroup.RecordTube(LOCATION(34 + X_, 192 + Y_));
	buildingGroup.RecordTube(LOCATION(34 + X_, 195 + Y_));

	AIHelper::RecordTubeOrWallLine(buildingGroup, 9 + X_, 165 + Y_, 17 + X_, 168 + Y_, map_id::mapLavaWall);
	AIHelper::RecordTubeOrWallLine(buildingGroup, 50 + X_, 162 + Y_, 53 + X_, 165 + Y_, map_id::mapLavaWall);
	AIHelper::RecordTubeOrWallLine(buildingGroup, 61 + X_, 167 + Y_, 64 + X_, 167 + Y_, map_id::mapLavaWall);
	AIHelper::RecordTubeOrWallLine(buildingGroup, 25 + X_, 162 + Y_, 25 + X_, 165 + Y_, map_id::mapLavaWall);
	AIHelper::RecordTubeOrWallLine(buildingGroup, 26 + X_, 162 + Y_, 28 + X_, 161 + Y_, map_id::mapLavaWall);
	AIHelper::RecordTubeOrWallLine(buildingGroup, 29 + X_, 161 + Y_, 37 + X_, 161 + Y_, map_id::mapLavaWall);

	AIHelper::RecordTubeOrWallLine(buildingGroup, 42 + X_, 161 + Y_, 45 + X_, 161 + Y_, map_id::mapLavaWall);
	AIHelper::RecordTubeOrWallLine(buildingGroup, 42 + X_, 162 + Y_, 42 + X_, 164 + Y_, map_id::mapLavaWall);

	AIHelper::RecordTubeOrWallLine(buildingGroup, 37 + X_, 162 + Y_, 37 + X_, 164 + Y_, map_id::mapLavaWall);

	//Tubes for other colony structures.
	buildingGroup.RecordTube(LOCATION(34 + X_, 208 + Y_)); 	//Tube for Robot Command Center
	buildingGroup.RecordTube(LOCATION(25 + X_, 189 + Y_));
	buildingGroup.RecordTube(LOCATION(22 + X_, 189 + Y_));
	buildingGroup.RecordTube(LOCATION(23 + X_, 199 + Y_));

	buildingGroup.RecordTube(LOCATION(15 + X_, 169 + Y_));
	buildingGroup.RecordTube(LOCATION(10 + X_, 169 + Y_));

	AIHelper::RecordTubeOrWallLine(buildingGroup, 10 + X_, 170 + Y_, 27 + 31, 170 + Y_, map_id::mapTube);

	//Colony to Western GuardPosts
	AIHelper::RecordTubeOrWallLine(buildingGroup, 20 + X_, 171 + Y_, 20 + X_, 187 + Y_, map_id::mapTube);

	AIHelper::RecordTubeOrWallLine(buildingGroup, 27 + X_, 166 + Y_, 27 + X_, 169 + Y_, map_id::mapTube);

	AIHelper::RecordTubeOrWallLine(buildingGroup, 28 + X_, 166 + Y_, 35 + X_, 166 + Y_, map_id::mapTube);

	AIHelper::RecordTubeOrWallLine(buildingGroup, 35 + X_, 165 + Y_, 51 + X_, 165 + Y_, map_id::mapTube);

	AIHelper::RecordTubeOrWallLine(buildingGroup, 51 + X_, 166 + Y_, 51 + X_, 172 + Y_, map_id::mapTube);

	AIHelper::RecordTubeOrWallLine(buildingGroup, 52 + X_, 172 + Y_, 63 + X_, 172 + Y_, map_id::mapTube);

	buildingGroup.RecordTube(LOCATION(63 + X_, 171 + Y_));

	buildingGroup.SetTargCount(map_id::mapConVec, map_id::mapNone, 1);
	buildingGroup.SetTargCount(map_id::mapEarthworker, map_id::mapNone, 1);
	buildingGroup.SetTargCount(map_id::mapRoboMiner, map_id::mapNone, 1);
	buildingGroup.RecordVehReinforceGroup(buildingGroup, 1);

	scriptGlobal.ColonyExpansionBuildGroup = buildingGroup;
}

Unit& AddNewBuildingToVector(std::vector<Unit> &buildingList, map_id buildingType, LOCATION location)
{
	Unit unit;
	TethysGame::CreateUnit(unit, buildingType, location, 1, map_id::mapNone, UnitDirection::North);

	buildingList.push_back(unit);

	return buildingList.back();
}

void BuildEnemyBase(UnitHelper::VehicleBuilder vehicleBuilderAI, LOCATION commonBeaconLoc, LOCATION rareBeaconLoc)
{
	MAP_RECT nonCombatSafeRect = MAP_RECT(LOCATION(10 + X_, 176 + Y_), LOCATION(46 + X_, 212 + Y_));

	Unit unit;
	std::vector<Unit> buildingVector;

	LOCATION loc = LOCATION(30 + X_, 208 + Y_);
	Unit commandCenter;
	TethysGame::CreateUnit(commandCenter, map_id::mapCommandCenter, loc, 1, map_id::mapNone, UnitDirection::East);

	Unit structFactory;
	TethysGame::CreateUnit(structFactory, map_id::mapStructureFactory, LOCATION(30 + X_, 202 + Y_), Player1, map_id::mapNone, UnitDirection::East);
	/*unit.SetFactoryCargo(0, mapCommandCenter, mapNone);*/

	Unit tokamak = AddNewBuildingToVector(buildingVector, map_id::mapTokamak, LOCATION(4 + X_, 177 + Y_));
	tokamak.SetDamage(TethysGame::GetRand(140));

	Unit vehicleFactory = AddNewBuildingToVector(buildingVector, map_id::mapVehicleFactory, LOCATION(18 + X_, 198 + Y_));

	Unit smelterRareEast = AddNewBuildingToVector(buildingVector, map_id::mapRareOreSmelter, LOCATION(42 + X_, 185 + Y_));
	Unit smelterRareWest = AddNewBuildingToVector(buildingVector, map_id::mapRareOreSmelter, LOCATION(35 + X_, 185 + Y_));
	Unit mineCommon = AddNewBuildingToVector(buildingVector, map_id::mapCommonOreMine, commonBeaconLoc);

	AddNewBuildingToVector(buildingVector, map_id::mapAgridome, LOCATION(30 + X_, 195 + Y_));

	Unit smelterCommonWest = AddNewBuildingToVector(buildingVector, map_id::mapCommonOreSmelter, LOCATION(49 + X_, 185 + Y_));
	Unit smelterCommonEast = AddNewBuildingToVector(buildingVector, map_id::mapCommonOreSmelter, LOCATION(55 + X_, 185 + Y_));

	//BUG: You must set mine type to common even though you are building a rare ore mine.
	Unit mineRare = AddNewBuildingToVector(buildingVector, map_id::mapCommonOreMine, rareBeaconLoc);

	AddNewBuildingToVector(buildingVector, map_id::mapCommonStorage, LOCATION(25 + X_, 196 + Y_));
	AddNewBuildingToVector(buildingVector, map_id::mapRareStorage, LOCATION(23 + X_, 196 + Y_));

	//Tubes Rare Smelters to Common Ore Smelters
	CreateTubeLine(LOCATION(20 + X_, 188 + Y_), LOCATION(55 + X_, 188 + Y_));

	//Tubes Rare Smelter to Agrigome to Structure Factory to Command Center
	CreateTubeLine(LOCATION(33 + X_, 189 + Y_), LOCATION(33 + X_, 208 + Y_));

	//Tubes Structure Factory to Vehicle Factory
	CreateTubeLine(LOCATION(32 + X_, 198 + Y_), LOCATION(19 + X_, 198 + Y_));

	//Needs UnitEx initialization for repair Convec
	TethysGame::CreateUnit(scriptGlobal.AIRepairConvec, map_id::mapConVec, LOCATION(22 + X_, 200 + Y_), Player1, map_id::mapNone, UnitDirection::East);
	scriptGlobal.AIRepairConvec.DoSetLights(true);

	Unit buildingConvec;
	Unit earthworker;
	vehicleBuilderAI.CreateVechLightsOn(buildingConvec, mapConVec, LOCATION(24 + X_, 200 + Y_), map_id::mapNone);
	vehicleBuilderAI.CreateVechLightsOn(earthworker, mapEarthworker, LOCATION(26 + X_, 178 + Y_), map_id::mapNone);

	LOCATION truckLoc = LOCATION(35 + X_, 180 + Y_);
	std::vector<Unit> trucks;

	scriptGlobal.ReinforceVehicleBuildGroup = CreateBuildingGroup(Player[1]);
	scriptGlobal.ReinforceVehicleBuildGroup.TakeUnit(vehicleFactory);

	MiningGroup miningGroup;
	MAP_RECT miningIdleRect = MAP_RECT(LOCATION(35 + X_, 176 + Y_), LOCATION(55 + X_, 182 + Y_));

	vehicleBuilderAI.SetupMiningGroup(miningGroup, mineCommon, smelterCommonWest, miningIdleRect, 3);
	scriptGlobal.ReinforceVehicleBuildGroup.RecordVehReinforceGroup(miningGroup, 3);

	vehicleBuilderAI.SetupMiningGroup(miningGroup, mineCommon, smelterCommonEast, miningIdleRect, 3);
	scriptGlobal.ReinforceVehicleBuildGroup.RecordVehReinforceGroup(miningGroup, 3);

	vehicleBuilderAI.SetupMiningGroup(miningGroup, mineRare, smelterRareWest, miningIdleRect, 3);
	scriptGlobal.ReinforceVehicleBuildGroup.RecordVehReinforceGroup(miningGroup, 2);

	vehicleBuilderAI.SetupMiningGroup(miningGroup, mineRare, smelterRareEast, miningIdleRect, 3);
	scriptGlobal.ReinforceVehicleBuildGroup.RecordVehReinforceGroup(miningGroup, 2);

	SetupBuildGroup(earthworker, buildingConvec, structFactory, vehicleFactory, buildingVector, nonCombatSafeRect);

	scriptGlobal.RepairGroup = CreateBuildingGroup(Player[1]);
	scriptGlobal.RepairGroup.SetRect(nonCombatSafeRect);
	scriptGlobal.RepairGroup.TakeUnit(scriptGlobal.AIRepairConvec);
	scriptGlobal.RepairGroup.SetTargCount(map_id::mapConVec, map_id::mapNone, 1);
	scriptGlobal.ReinforceVehicleBuildGroup.RecordVehReinforceGroup(scriptGlobal.RepairGroup, 2);

	SetupAIResources();
}