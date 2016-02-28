#pragma once

#include "ScriptGlobal.h"
#include "UnitHelper.h"
#include "Outpost2DLL\Outpost2DLL.h"
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
		void SetupBaseDefenseFightGroup(FightGroup &fightGroup);
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
		void AIFightGroupMaker::CreateEndScorpAttack(LOCATION startLoc);
		void AIFightGroupMaker::CreateEndRpgAttack(LOCATION startLoc);
	};

    LOCATION GetRandSouthernVehicleStartLoc();
    
}