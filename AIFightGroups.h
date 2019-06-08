#pragma once

#include "ScriptGlobal.h"
#include "UnitHelper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include <vector>

namespace AIFightGroups
{
	enum class FightGroupLevel
	{
		Initial,
		Middle,
		End
	};

	class AIFightGroupMaker
	{
	public:
		map_id AIFightGroupMaker::GetAttackTarget(int playerNumber);
		LOCATION GetRandSouthernVehicleStartLoc();
		void AIFightGroupMaker::SetupBaseDefenseFightGroup(FightGroup &fightGroup);
		void AIFightGroupMaker::CreateRareOreMineAttack();
		void AIFightGroupMaker::CreateSpaceportAttack();
		void AIFightGroupMaker::CreatePhoenixModuleAttack();
		void CreateRandomFightGroup(FightGroupLevel fightGroupLevel);
		
		UnitHelper::VehicleBuilder VehicleBuilderAI;

	private:
		void AIFightGroupMaker::CreateInitialFightGroup(LOCATION startLoc);
		void AIFightGroupMaker::CreateMiddleFightGroup(LOCATION startLoc);
		void AIFightGroupMaker::CreateEndFightGroup(LOCATION startLoc);

		void AIFightGroupMaker::CreateInitialMixedAttack(LOCATION startLoc);
		void AIFightGroupMaker::CreateInitialStealthAttack(LOCATION startLoc);
		void AIFightGroupMaker::CreateInitialScorpAttack(LOCATION startLoc);

		void AIFightGroupMaker::CreateMiddleMixedAttack(LOCATION startLoc);
		void AIFightGroupMaker::CreateMiddleScorpAttack(LOCATION startLoc);
		void AIFightGroupMaker::CreateMiddleStealthAttack(LOCATION startLoc);

		void AIFightGroupMaker::CreateEndMixedAttack(LOCATION startLoc);
		void AIFightGroupMaker::CreateEndRpgAttack(LOCATION startLoc);

		void AIFightGroupMaker::addToTargetVectorIfBuildingExists(std::vector<map_id> &targets, int playerNumber, map_id mapID);
	};
}
