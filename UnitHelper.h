#pragma once

#include "OP2Helper\OP2Helper.h"
#include "HFL\Source\HFL.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>
#include <functional>

namespace UnitHelper
{
	class VehicleBuilder
	{
	public:
		void SetPlayer(int player);
		int GetPlayer();
		void SetVehicleDirection(UnitDirection unitDirection);
		UnitDirection GetVehicleDirection();

		void SetupMiningGroup(MiningGroup &miningGroup, Unit &mine, Unit &smelter, MAP_RECT &oreIdleRect, int numbOfTrucks);
		void PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units);
		void PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units, map_id target);
		void CreateVechLightsOn(Unit &unit, map_id vehicleType, LOCATION location, map_id cargo);

		void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, const map_id vehicleType, const map_id cargo, int vehicleCount);
		void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, map_id vehicleType, const std::vector<map_id> &cargoVector);
		void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, const std::vector<map_id> &vehicleTypes);

		void VehicleBuilder::CreateLineOfTrucksWithCargo(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, const std::vector<Truck_Cargo> &cargoTypes);

		void VehicleBuilder::CauseRandomDamage(std::vector<Unit> &units, int percentChanceDamaged, int minDamage, int maxDamage);

		void VehicleBuilder::MoveRelativeAmount(std::vector<Unit> &units, LOCATION relativeMoveAmount);

	private:
		int playerNumber = 0;
		UnitDirection unitDirection = UnitDirection::North;

		std::function<LOCATION(LOCATION, int)> VehicleBuilder::getLineDirectionIterator(UnitDirection lineDirection);
	};


	bool BuildingConstructed(int playerNumber, map_id buildingType);
	bool KitInConVec(int player, map_id structureKitType);
	bool KitInStructFactory(int playerNumber, map_id structureKitType);
	bool BuildingOrKitAvailable(int playerNumber, map_id buildingType);
	bool IsCombatUnit(map_id unitType);
	void FindBuildings(std::vector<Unit> &buildings, int playerNumber, const std::vector<map_id> &buildingTypes);
	void FindBuildingLocations(std::vector<LOCATION> &locations, int playerNumber, const std::vector<map_id> &buildingTypes);
	int FindSouthernYCoordOfCombatant(int playerNumber);
}