#include "AIFightGroups.h"

namespace AIFightGroups
{
void addToTargetVectorIfExists(std::vector<map_id> &targets, map_id mapID)
{
	if (UnitHelper::BuildingConstructed(0, mapID))
	{
		targets.push_back(mapID);
	}
}

map_id GetAttackTarget()
{
	std::vector<map_id> potentialTargets;

	addToTargetVectorIfExists(potentialTargets, map_id::mapCommandCenter);
	addToTargetVectorIfExists(potentialTargets, map_id::mapTokamak);
	addToTargetVectorIfExists(potentialTargets, map_id::mapStructureFactory);
	addToTargetVectorIfExists(potentialTargets, map_id::mapCommonOreSmelter);
	addToTargetVectorIfExists(potentialTargets, map_id::mapRareOreSmelter);
	addToTargetVectorIfExists(potentialTargets, map_id::mapRareOreMine);
	addToTargetVectorIfExists(potentialTargets, map_id::mapCommonOreMine);
	addToTargetVectorIfExists(potentialTargets, map_id::mapSpaceport);
	addToTargetVectorIfExists(potentialTargets, map_id::mapVehicleFactory);
	addToTargetVectorIfExists(potentialTargets, map_id::mapAdvancedLab);

	return potentialTargets[TethysGame::GetRand(potentialTargets.size())];
}

LOCATION GetRandSouthernVehicleStartLoc()
{
	return MAP_RECT(LOCATION(1 + X_, 256 + Y_), LOCATION(53 + X_, 256 + Y_)).RandPt();
}

void AIFightGroupMaker::CreateRareOreMineAttack()
{
	LOCATION startLoc = GetRandSouthernVehicleStartLoc();

	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapLynx, map_id::mapRPG, 8);

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.SpecialFightGroup, units, mapRareOreMine);

	scriptGlobal.TrigRareMineDestroyed.Disable();
	scriptGlobal.TrigRandomFightGroup.Enable();
}

void AIFightGroupMaker::CreateSpaceportAttack()
{
	LOCATION startLoc = GetRandSouthernVehicleStartLoc();

	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapPanther, std::vector<map_id> {
		map_id::mapEMP, map_id::mapRPG, map_id::mapESG, map_id::mapStickyfoam, map_id::mapEMP,
		map_id::mapESG, map_id::mapRPG, map_id::mapEMP, map_id::mapStickyfoam, map_id::mapRPG });

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.SpecialFightGroup, units, map_id::mapSpaceport);

	scriptGlobal.TrigSpaceportBuilt.Disable();
}

void AIFightGroupMaker::CreatePhoenixModuleAttack()
{
	LOCATION startLoc = GetRandSouthernVehicleStartLoc();

	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapTiger, std::vector<map_id> {
		map_id::mapEMP, map_id::mapRPG, map_id::mapRPG, map_id::mapStickyfoam, map_id::mapESG, map_id::mapRPG, map_id::mapEMP,
			map_id::mapEMP, map_id::mapESG, map_id::mapRPG, map_id::mapRPG, map_id::mapEMP, map_id::mapRPG, map_id::mapESG });

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.SpecialFightGroup, units, map_id::mapSpaceport);

	scriptGlobal.TrigPhoenixModuleResearched.Disable();
}

void AIFightGroupMaker::CreateInitialMixedAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapLynx, std::vector<map_id> {
		map_id::mapStickyfoam, map_id::mapMicrowave, map_id::mapMicrowave, map_id::mapMicrowave,
			map_id::mapMicrowave, map_id::mapMicrowave, map_id::mapMicrowave, map_id::mapStickyfoam});

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());
}

void AIFightGroupMaker::CreateInitialStealthAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapLynx, std::vector<map_id> {
		map_id::mapEMP, map_id::mapStarflare, map_id::mapStickyfoam, map_id::mapStarflare, map_id::mapRPG, map_id::mapRPG });

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());

	scriptGlobal.PeriodicFightGroup.SetLights(false);
}

void AIFightGroupMaker::CreateInitialScorpAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapScorpion, map_id::mapEnergyCannon, 12);
	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc + LOCATION(0, -1), 1, map_id::mapScorpion, map_id::mapEnergyCannon, 6);

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());
}

void AIFightGroupMaker::CreateMiddleMixedAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapPanther, std::vector<map_id> {
		map_id::mapStickyfoam, map_id::mapMicrowave, map_id::mapMicrowave, map_id::mapRPG,
			map_id::mapEMP, map_id::mapEMP, map_id::mapStickyfoam});

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());
}


void AIFightGroupMaker::CreateMiddleStealthAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapLynx, std::vector<map_id> {
		map_id::mapEMP, map_id::mapSupernova, map_id::mapStickyfoam, map_id::mapSupernova, map_id::mapRPG, map_id::mapRPG, map_id::mapSupernova, map_id::mapEMP });

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());

	scriptGlobal.PeriodicFightGroup.SetLights(false);
}

void AIFightGroupMaker::CreateMiddleScorpAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapScorpion, map_id::mapEnergyCannon, 12);
	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc + LOCATION(0, -1), 1, map_id::mapScorpion, map_id::mapEnergyCannon, 12);

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());
}

void AIFightGroupMaker::CreateEndScorpAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapScorpion, map_id::mapEnergyCannon, 12);
	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc + LOCATION(0, -1), 1, map_id::mapScorpion, map_id::mapEnergyCannon, 12);
	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapScorpion, map_id::mapEnergyCannon, 8);

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());
}

void AIFightGroupMaker::CreateEndRpgAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapTiger, map_id::mapRPG, 12);

	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());
}

void AIFightGroupMaker::CreateEndMixedAttack(LOCATION startLoc)
{
	std::vector<Unit> units;

	VehicleBuilderAI.CreateHorizLineOfVehicles(units, startLoc, 1, map_id::mapTiger, std::vector<map_id> {
		map_id::mapStickyfoam, map_id::mapRPG, map_id::mapESG, map_id::mapEMP,
			map_id::mapRPG, map_id::mapEMP, map_id::mapESG});


	VehicleBuilderAI.PopulateFightGroup(scriptGlobal.PeriodicFightGroup, units, GetAttackTarget());
}

void AIFightGroupMaker::CreateInitialFightGroup(LOCATION startLoc)
{
	int group = TethysGame::GetRand(3);

	switch (group)
	{
	case 0:
		CreateInitialMixedAttack(startLoc);
		break;
	case 1:
		CreateInitialScorpAttack(startLoc);
		break;
	case 2:
		CreateInitialStealthAttack(startLoc);
		break;
	}
}

void AIFightGroupMaker::CreateMiddleFightGroup(LOCATION startLoc)
{
	int group = TethysGame::GetRand(3);

	switch (group)
	{
	case 0:
		CreateMiddleMixedAttack(startLoc);
		break;
	case 1:
		CreateMiddleScorpAttack(startLoc);
		break;
	case 2:
		CreateMiddleStealthAttack(startLoc);
		break;
	}
}

void AIFightGroupMaker::CreateEndFightGroup(LOCATION startLoc)
{
	int group = TethysGame::GetRand(3);

	switch (group)
	{
	case 0:
		CreateEndRpgAttack(startLoc);
		break;
	case 1:
		CreateEndScorpAttack(startLoc);
		break;
	case 2:
		CreateEndMixedAttack(startLoc);
		break;
	}
}

void AIFightGroupMaker::CreateRandomFightGroup(FightGroupLevel fightGroupLevel)
{
	LOCATION startLoc = GetRandSouthernVehicleStartLoc();

	switch (fightGroupLevel)
	{
	case FightGroupLevel::Initial:
		CreateInitialFightGroup(startLoc);
		break;
	case FightGroupLevel::Middle:
		CreateMiddleFightGroup(startLoc);
		break;
	case FightGroupLevel::End:
		CreateEndFightGroup(startLoc);
		break;
	}
}

void AIFightGroupMaker::SetupBaseDefenseFightGroup(FightGroup &fightGroup)
{
	std::vector<Unit> units;
	VehicleBuilderAI.CreateHorizLineOfVehicles(units, LOCATION(11 + X_, 179 + Y_), 2, map_id::mapLynx, map_id::mapMicrowave, 6);

	VehicleBuilderAI.PopulateFightGroup(fightGroup, units);

	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapMicrowave, 8);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapRPG, 4);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapEMP, 4);
	fightGroup.SetTargCount(map_id::mapLynx, map_id::mapStickyfoam, 4);

	fightGroup.SetRect(MAP_RECT(LOCATION(1 + X_, 166 + Y_), LOCATION(64 + X_, 217 + Y_)));
}
}