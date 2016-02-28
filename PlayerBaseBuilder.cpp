#include "PlayerBaseBuilder.h"

void SetStartingSupplies()
{
	InitPlayerResources(0, CES1ResourceSet);
	Player[0].CenterViewOn(28 + X_, 51 + Y_);


	//Player[0].SetRareOre(0);
	//Player[0].SetKids(12);
	//Player[0].SetScientists(15);
}

void BuildPlayerBase()
{
	UnitHelper::VehicleBuilder vehicleBuilder;

	Unit unit;
	TethysGame::CreateUnit(unit, map_id::mapCommandCenter, LOCATION(24 + X_, 48 + Y_), 0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapAgridome, LOCATION(32 + X_, 48 + Y_), 0, map_id::mapNone, 0);
	TethysGame::CreateUnit(unit, map_id::mapStructureFactory, LOCATION(24 + X_, 55 + Y_), 0, map_id::mapNone, 0);
	/*y.SetFactoryCargo(0, map_id::mapCommandCenter, map_id::mapNone);*/
	TethysGame::CreateUnit(unit, mapCommonOreSmelter, LOCATION(32 + X_, 55 + Y_), 0, map_id::mapNone, 0);

	//CC to Agridome
	CreateTubeOrWallLine(25 + X_, 48 + Y_, 31 + X_, 48 + Y_, mapTube);

	//CC to Struct Factory
	CreateTubeOrWallLine(24 + X_, 49 + Y_, 24 + X_, 55 + Y_, mapTube);

	//CC to Smelter
	CreateTubeOrWallLine(24 + X_, 55 + Y_, 32 + X_, 55 + Y_, mapTube);

	TethysGame::CreateUnit(unit, mapTokamak, LOCATION(6 + X_, 55 + Y_), 0, mapNone, 0);

	LOCATION loc = LOCATION(22 + X_, 59 + Y_);
	std::vector<Unit> units;
	vehicleBuilder.CreateHorizLineOfVehicles(units, loc, 2, std::vector<map_id> {
		map_id::mapConVec, map_id::mapConVec, map_id::mapEarthworker, map_id::mapRoboMiner,
		map_id::mapRoboSurveyor, map_id::mapCargoTruck, map_id::mapCargoTruck, map_id::mapRoboDozer});

	SetStartingSupplies();
}