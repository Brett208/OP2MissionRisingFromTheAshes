#include "UnitHelper.h"

namespace UnitHelper
{
	void VehicleBuilder::SetPlayer(int player)
	{
		if (playerNumber > 6)
		{
			throw "Maximum of 6 players allowed.";//std::invalid_argument();
		}

		playerNumber = player;
	}

	int VehicleBuilder::GetPlayer()
	{
		return playerNumber;
	}
	
	void VehicleBuilder::SetVehicleDirection(UnitDirection direction)
	{
		unitDirection = direction;
	}
	
	UnitDirection VehicleBuilder::GetVehicleDirection()
	{
		return unitDirection;
	}

	void VehicleBuilder::CreateVechLightsOn(Unit &unit, map_id vehicleType, LOCATION location, map_id cargo)
	{
		TethysGame::CreateUnit(unit, vehicleType, location, playerNumber, cargo, unitDirection);
		unit.DoSetLights(true);
	}

	void VehicleBuilder::SetupMiningGroup(
		MiningGroup &miningGroup, const Unit &vehicleFactory, Unit &mine, Unit &smelter, MAP_RECT &oreIdleRect, int numbOfTrucks)
	{
		miningGroup = CreateMiningGroup(Player[1]);

		LOCATION smelterLoc = smelter.Location();
		miningGroup.Setup(mine, smelter, oreIdleRect);

		Unit truck;
		for (int i = 0; i < numbOfTrucks; ++i)
		{
			CreateVechLightsOn(truck, map_id::mapCargoTruck, oreIdleRect.RandPt(), map_id::mapNone);
			miningGroup.TakeUnit(truck);
		}

		miningGroup.SetTargCount(map_id::mapCargoTruck, map_id::mapNone, numbOfTrucks);
	}

	void VehicleBuilder::PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units)
	{
		fightGroup = CreateFightGroup(playerNumber);

		for (Unit unit : units)
		{
			fightGroup.TakeUnit(unit);
		}
	}

	void VehicleBuilder::PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units, map_id target)
	{
		PopulateFightGroup(fightGroup, units);

		fightGroup.SetAttackType(target);
		fightGroup.DoAttackEnemy();
	}

	void VehicleBuilder::CreateHorizLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, int vehicleSpacing, const map_id vehicleType, const map_id cargo, int vehicleCount)
	{
		Unit unit;
		for (int i = 0; i < vehicleCount; ++i)
		{
			LOCATION loc = startLoc + LOCATION(i * vehicleSpacing, 0);
			CreateVechLightsOn(unit, vehicleType, loc, cargo);
			units.push_back(unit);
		}
	}

	void VehicleBuilder::CreateHorizLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, int vehicleSpacing, map_id vehicleType, const std::vector<map_id> &cargoVector)
	{
		Unit unit;
		LOCATION loc;

		for (size_t i = 0; i < cargoVector.size(); ++i)
		{
			loc = startLoc + LOCATION(i * vehicleSpacing, 0);
			CreateVechLightsOn(unit, vehicleType, loc, cargoVector[i]);
			units.push_back(unit);
		}
	}

	void VehicleBuilder::CreateHorizLineOfVehicles(
		std::vector<Unit> &units, LOCATION startLoc, int vehicleSpacing, const std::vector<map_id> &vehicleTypes)
	{
		Unit unit;
		for (size_t i = 0; i < vehicleTypes.size(); ++i)
		{
			LOCATION loc = startLoc + LOCATION(i * vehicleSpacing, 0);
			CreateVechLightsOn(unit, vehicleTypes[i], loc, map_id::mapNone);
			units.push_back(unit);
		}
	}

	bool BuildingConstructed(int player, map_id buildingType)
	{
		Unit structure;
		PlayerBuildingEnum findStructures(player, buildingType);

		while (findStructures.GetNext(structure))
		{
			return true;
		}

		return false;
	}

	bool KitInConVec(int player, map_id structureKitType)
	{
		Unit vehicle;
		PlayerUnitEnum findAllVehicles(player);

		while (findAllVehicles.GetNext(vehicle))
		{
			if (vehicle.GetType() == mapConVec && vehicle.GetCargo() == structureKitType)
			{
				return true;
			}
		}

		return false;
	}

	bool KitInStructFactory(int player, map_id structureKitType)
	{
		// Below Requires HFL/UnitEx for GetFactoryCargo.
		UnitEx nextSF;
		PlayerBuildingEnum findAllSFs(player, mapStructureFactory);

		while (findAllSFs.GetNext(nextSF))
		{
			for (int i = 0; i < 6; ++i)
			{
				if (nextSF.GetFactoryCargo(i) == structureKitType)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool BuildingOrKitAvailable(int player, map_id buildingType)
	{
		return BuildingConstructed(player, buildingType) ||
			KitInConVec(player, buildingType) ||
			KitInStructFactory(player, buildingType);
	}

	bool IsCombatUnit(map_id unitType)
	{
		return unitType == map_id::mapLynx ||
			unitType == map_id::mapPanther ||
			unitType == map_id::mapTiger ||
			unitType == map_id::mapScorpion;
	}

	void FindBuildings(std::vector<Unit> &buildings, int playerNumber, const std::vector<map_id> &buildingTypes)
	{
		for (map_id mapID : buildingTypes)
		{
			PlayerBuildingEnum playerBuildingEnum = PlayerBuildingEnum(playerNumber, mapID);
			Unit unit;

			while (playerBuildingEnum.GetNext(unit))
			{
				buildings.push_back(unit);
				break;
			}
		}
	}

	void FindBuildingLocations(std::vector<LOCATION> &locations, int playerNumber, const std::vector<map_id> &buildingTypes)
	{
		std::vector<Unit> buildings;
		FindBuildings(buildings, playerNumber, buildingTypes);

		for (Unit unit : buildings)
		{
			locations.push_back(unit.Location());
		}
	}

	int FindSouthernYCoordOfCombatant(int playerNumber)
	{
		PlayerVehicleEnum vehicleEnum(playerNumber);
		Unit unit;
		int southernYCoordOfUnit = 0;

		while (vehicleEnum.GetNext(unit))
		{
			if (UnitHelper::IsCombatUnit(unit.GetType()) &&
				unit.Location().y > southernYCoordOfUnit)
			{
				southernYCoordOfUnit = unit.Location().y;
			}
		}

		return southernYCoordOfUnit;
	}
}