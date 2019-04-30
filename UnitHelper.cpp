#include "UnitHelper.h"

namespace UnitHelper
{
	void VehicleBuilder::SetPlayer(int player)
	{
		if (playerNumber > 6)
		{
			throw "Maximum of 6 players allowed.";
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
		MiningGroup &miningGroup, Unit &mine, Unit &smelter, MAP_RECT &oreIdleRect, int numbOfTrucks)
	{
		miningGroup = CreateMiningGroup(Player[1]);

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

	std::function<LOCATION(LOCATION, int)> VehicleBuilder::getLineDirectionIterator(UnitDirection lineDirection)
	{
		switch (lineDirection)
		{
		case UnitDirection::South:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(0, spacing); };

		case UnitDirection::SouthWest:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(-spacing, spacing); };

		case UnitDirection::West:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(-spacing, 0); };

		case UnitDirection::NorthWest:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(-spacing, -spacing); };

		case UnitDirection::North:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(0, -spacing); };

		case UnitDirection::NorthEast:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(spacing, -spacing); };

		case UnitDirection::East:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(spacing, 0); };

		case UnitDirection::SouthEast:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(spacing, spacing); };
		}

		throw "Invalid UnitDirection passed into Function.";
	}

	void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, const map_id vehicleType, const map_id cargo, int vehicleCount)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;
		for (int i = 0; i < vehicleCount; ++i)
		{
			CreateVechLightsOn(unit, vehicleType, currentLoc, cargo);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, map_id vehicleType, const std::vector<map_id> &cargoVector)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;

		for (size_t i = 0; i < cargoVector.size(); ++i)
		{
			CreateVechLightsOn(unit, vehicleType, currentLoc, cargoVector[i]);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, const std::vector<map_id> &vehicleTypes)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;
		for (size_t i = 0; i < vehicleTypes.size(); ++i)
		{
			CreateVechLightsOn(unit, vehicleTypes[i], currentLoc, map_id::mapNone);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::CreateLineOfTrucksWithCargo(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, const std::vector<Truck_Cargo> &cargoTypes)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;
		for (size_t i = 0; i < cargoTypes.size(); ++i)
		{
			CreateVechLightsOn(unit, map_id::mapCargoTruck, currentLoc, map_id::mapNone);
			unit.SetTruckCargo(cargoTypes[i], 1000);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::CauseRandomDamage(std::vector<Unit> &units, int percentChanceDamaged, int minDamage, int maxDamage)
	{
		if (maxDamage < minDamage)
		{
			throw "maxDamage must be greater than minDamage.";
		}

		if (percentChanceDamaged > 100 || percentChanceDamaged < 0)
		{
			throw "percentChanceDamaged must be between 0 and 100.";
		}

		for (Unit unit : units)
		{
			if (TethysGame::GetRand(100) <= percentChanceDamaged)
			{
				double percentOfMaxDamage = static_cast<double>(TethysGame::GetRand(100)) / static_cast<double>(100);
				int damage = minDamage + static_cast<int>((percentOfMaxDamage * static_cast<double>((maxDamage - minDamage))));
				unit.SetDamage(damage);
			}
		}
	}

	void VehicleBuilder::MoveRelativeAmount(std::vector<Unit> &units, LOCATION relativeMoveAmount)
	{
		for (Unit unit : units)
		{
			unit.DoMove(unit.Location() + relativeMoveAmount);
		}
	}

	bool BuildingConstructed(int playerNumber, map_id buildingType)
	{
		Unit structure;
		PlayerBuildingEnum playerBuildingEnum(playerNumber, buildingType);

		while (playerBuildingEnum.GetNext(structure))
		{
			return true;
		}

		return false;
	}

	bool KitInConVec(int playerNumber, map_id structureKitType)
	{
		Unit vehicle;
		PlayerVehicleEnum playerVehicleEnum(playerNumber);

		while (playerVehicleEnum.GetNext(vehicle))
		{
			if (vehicle.GetType() == mapConVec && vehicle.GetCargo() == structureKitType)
			{
				return true;
			}
		}

		return false;
	}

	bool KitInStructFactory(int playerNumber, map_id structureKitType)
	{
		// Below Requires HFL/UnitEx for GetFactoryCargo.
		UnitEx nextSF;
		PlayerBuildingEnum findAllSFs(playerNumber, mapStructureFactory);

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