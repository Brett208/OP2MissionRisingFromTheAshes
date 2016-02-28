#pragma once

#include "HFL\Source\HFL.h"
#include "outpost2DLL/Outpost2DLL.h"

struct ScriptGlobal
{
	Trigger TrigVictorySkydock;
	Trigger TrigVictoryFood;
	Trigger TrigVictoryCommonMetals;
	Trigger TrigVictoryRareMetals;
	Trigger TrigVictoryColonists;

	Trigger TrigFailureWaitTime;

	Trigger TrigDisaster;
	Trigger TrigVolcanoEruption;

	Trigger TrigRandomFightGroup;
	Trigger TrigSpaceportBuilt;
	Trigger TrigRareMineDestroyed;
	Trigger TrigPhoenixModuleResearched;
	Trigger TrigAIBaseReinforcement;

	FightGroup SpecialFightGroup;
	FightGroup PeriodicFightGroup;
	FightGroup BaseDefenseFightGroup;

	BuildingGroup ReinforceVehicleBuildGroup;
	BuildingGroup ColonyExpansionBuildGroup;
	BuildingGroup RepairGroup;

	UnitEx AIRepairConvec;

	bool AIVehicleFactoryDestoryed = false;
};

extern ScriptGlobal scriptGlobal;