#include "PlayerBaseBuilder.h"

void SetStartingSupplies()
{
	InitPlayerResources(Player0, CES1ResourceSet);
	Player[0].CenterViewOn(28 + X_, 51 + Y_);
}

void BuildPlayerBase()
{
	UnitHelper::VehicleBuilder vehicleBuilder;

	Unit unit;
	TethysGame::CreateUnit(unit, map_id::mapCommandCenter, LOCATION(24 + X_, 48 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapAgridome, LOCATION(32 + X_, 48 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapStructureFactory, LOCATION(24 + X_, 55 + Y_), Player0, map_id::mapNone, 0);
	/*y.SetFactoryCargo(0, map_id::mapCommandCenter, map_id::mapNone);*/
	TethysGame::CreateUnit(unit, mapCommonOreSmelter, LOCATION(32 + X_, 55 + Y_), Player0, map_id::mapNone, 0);

	//CC to Agridome
	CreateTubeOrWallLine(25 + X_, 48 + Y_, 31 + X_, 48 + Y_, mapTube);

	//CC to Struct Factory
	CreateTubeOrWallLine(24 + X_, 49 + Y_, 24 + X_, 55 + Y_, mapTube);

	//CC to Smelter
	CreateTubeOrWallLine(24 + X_, 55 + Y_, 32 + X_, 55 + Y_, mapTube);

	TethysGame::CreateUnit(unit, mapTokamak, LOCATION(6 + X_, 55 + Y_), Player0, map_id::mapNone, 0);

	LOCATION loc = LOCATION(22 + X_, 59 + Y_);
	std::vector<Unit> units;

	std::vector<map_id> vehicleTypes { map_id::mapConVec, map_id::mapConVec, map_id::mapEarthworker, map_id::mapRoboMiner,
		map_id::mapRoboSurveyor, map_id::mapCargoTruck, map_id::mapCargoTruck, map_id::mapRoboDozer };
	vehicleBuilder.CreateLineOfVehicles(units, loc, UnitDirection::East, 2, vehicleTypes);

	SetStartingSupplies();
}

void MarkResearchComplete(PlayerNum playerNumber, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	while (*format != '\0')
	{
		Player[playerNumber].MarkResearchComplete(va_arg(args, int));
		++format;
	}

	va_end(args);
}

void MakeBasePowerfulForDebug()
{
	_Player player = Player[0];

	player.SetWorkers(200);
	player.SetScientists(100);
	player.SetKids(100);
	player.SetFoodStored(90'000);
	player.SetOre(90'000);
	player.SetRareOre(90'000);
	player.SetTechLevel(10);

	MarkResearchComplete(Player0, "iiiiiiiiiiiii", 10401, 8901, 8951, 10206, 10209, 10202, 8801, 10305, 10205, 10208, 10204, 8601, 10101);


	UnitHelper::VehicleBuilder vehicleBuilder;

	LOCATION loc = LOCATION(22 + X_, 62 + Y_);
	std::vector<Unit> units;
	vehicleBuilder.CreateLineOfVehicles(units, loc, UnitDirection::East, 1, map_id::mapTiger, map_id::mapThorsHammer, 32);
	vehicleBuilder.CreateLineOfVehicles(units, loc + LOCATION(0, 1), UnitDirection::East, 1, map_id::mapTiger, map_id::mapEMP, 32);
	vehicleBuilder.CreateLineOfVehicles(units, loc + LOCATION(0, 2), UnitDirection::East, 1, map_id::mapTiger, map_id::mapThorsHammer, 32);

	Unit unit;
	TethysGame::CreateUnit(unit, map_id::mapCommonStorage, LOCATION(25 + X_, 45 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapCommonStorage, LOCATION(27 + X_, 45 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapCommonStorage, LOCATION(29 + X_, 45 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapCommonStorage, LOCATION(31 + X_, 45 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapCommonStorage, LOCATION(33 + X_, 45 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapCommonStorage, LOCATION(35 + X_, 45 + Y_), Player0, map_id::mapNone, 0);

	TethysGame::CreateUnit(unit, map_id::mapRareStorage, LOCATION(25 + X_, 42 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapRareStorage, LOCATION(27 + X_, 42 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapRareStorage, LOCATION(29 + X_, 42 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapRareStorage, LOCATION(31 + X_, 42 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapRareStorage, LOCATION(33 + X_, 42 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapRareStorage, LOCATION(35 + X_, 42 + Y_), Player0, map_id::mapNone, 0);

	TethysGame::CreateUnit(unit, map_id::mapSpaceport, LOCATION(21 + X_, 42 + Y_), Player0, map_id::mapNone, 0);
	unit.SetFactoryCargo(0, map_id::mapSkydock, map_id::mapNone);
	unit.SetFactoryCargo(1, map_id::mapSensorPackage, map_id::mapNone);
	unit.SetFactoryCargo(2, map_id::mapFusionDriveModule, map_id::mapNone);
	unit.SetFactoryCargo(3, map_id::mapIonDriveModule, map_id::mapNone);
	unit.SetFactoryCargo(4, map_id::mapCommandModule, map_id::mapNone);

	TethysGame::CreateUnit(unit, map_id::mapSpaceport, LOCATION(26 + X_, 38 + Y_), Player0, map_id::mapNone, 0);
	unit.SetFactoryCargo(0, map_id::mapOrbitalPackage, map_id::mapNone);
	unit.SetFactoryCargo(1, map_id::mapPhoenixModule, map_id::mapNone);
	unit.SetFactoryCargo(2, map_id::mapStasisSystems, map_id::mapNone);
	unit.SetFactoryCargo(3, map_id::mapHabitatRing, map_id::mapNone);
	unit.SetFactoryCargo(4, map_id::mapFuelingSystems, map_id::mapNone);

	TethysGame::CreateUnit(unit, map_id::mapAdvancedLab, LOCATION(16 + X_, 42 + Y_), Player0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapTokamak, LOCATION(12 + X_, 48 + Y_), Player0, map_id::mapNone, 0);

	TethysGame::ForceMoraleGreat(0);
}