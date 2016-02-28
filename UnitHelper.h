#pragma once

#include "OP2Helper\OP2Helper.h"
#include "HFL\Source\HFL.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

namespace UnitHelper
{
	class VehicleBuilder
	{
	public:
		void SetPlayer(int player);
		int GetPlayer();
		void SetVehicleDirection(UnitDirection unitDirection);
		UnitDirection GetVehicleDirection();

		void SetupMiningGroup(MiningGroup &miningGroup, const Unit &vehicleFactory, Unit &mine, Unit &smelter, MAP_RECT &oreIdleRect, int numbOfTrucks);
		void PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units);
		void PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units, map_id target);
		void CreateVechLightsOn(Unit &unit, map_id vehicleType, LOCATION location, map_id cargo);
		void CreateHorizLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, int vehicleSpacing, const map_id vehicleType, const map_id cargo, int vehicleCount);
		void CreateHorizLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, int vehicleSpacing, map_id vehicleType, const std::vector<map_id> &cargoVector);
		void CreateHorizLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, int vehicleSpacing, const std::vector<map_id> &vehicleTypes);

	private:
		int playerNumber = 0;
		UnitDirection unitDirection = UnitDirection::North;
	};


	bool BuildingConstructed(int player, map_id buildingType);
	bool KitInConVec(int player, map_id structureKitType);
	bool KitInStructFactory(int player, map_id structureKitType);
	bool BuildingOrKitAvailable(int player, map_id buildingType);
	bool IsCombatUnit(map_id unitType);
	void FindBuildings(std::vector<Unit> &buildings, int playerNumber, const std::vector<map_id> &buildingTypes);
	void FindBuildingLocations(std::vector<LOCATION> &locations, int playerNumber, const std::vector<map_id> &buildingTypes);
	int FindSouthernYCoordOfCombatant(int playerNumber);
}