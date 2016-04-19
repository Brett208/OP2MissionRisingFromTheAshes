#include "Disasters.h"

LOCATION getRandMapLoc()
{
	return LOCATION(
		TethysGame::GetRand(64) + X_,
		TethysGame::GetRand(256) + Y_);
}

double DistanceBetweenPoints(LOCATION loc1, LOCATION loc2)
{
	return std::sqrt(std::pow(loc2.x - loc1.x, 2) + std::pow(loc2.y - loc1.y, 2));
}

void CreateMeteor(const std::vector<LOCATION> &criticalBuildingLocations)
{
	LOCATION disasterLoc = getRandMapLoc();

	int meteorSizeSwitch = TethysGame::GetRand(10);
	int meteorSize;

	if (meteorSizeSwitch <= 4)
	{
		meteorSize = 0;
	}
	else if (meteorSizeSwitch <= 8)
	{
		meteorSize = 1;
	}
	else
	{
		meteorSize = 2;
		
		//Prevents large meteors until after 200 marks.
		if (TethysGame::Tick() < 200 * 100)
		{
			meteorSize = 1;
		}

		//Loops through areas around critical structures. If large meteor is going to hit one, tries a different point.
		for (size_t i = 0; i < criticalBuildingLocations.size(); ++i)
		{
			if (DistanceBetweenPoints(criticalBuildingLocations[i], disasterLoc) < 5)
			{
				disasterLoc = getRandMapLoc();
				i = -1;
			}
		}
	}

	TethysGame::SetMeteor(disasterLoc.x, disasterLoc.y, meteorSize);
}

void CreateStorm()
{
	LOCATION startLoc = getRandMapLoc();
	LOCATION endLoc = getRandMapLoc();

	while (DistanceBetweenPoints(startLoc, endLoc) < 60)
	{
		endLoc = getRandMapLoc();
	}

	TethysGame::SetLightning(
		startLoc.x, startLoc.y, TethysGame::GetRand(55), endLoc.x, endLoc.y);
}

void CreateEarthquake()
{
	LOCATION loc = getRandMapLoc();

	TethysGame::SetEarthquake(loc.x, loc.y, TethysGame::GetRand(2));
}

void CreateVortex()
{
	MAP_RECT vortexArea = MAP_RECT(LOCATION(1 + X_, 100 + Y_), LOCATION(64 + X_, 148 + Y_));
	LOCATION startLoc = vortexArea.RandPt();
	LOCATION endLoc = vortexArea.RandPt();

	TethysGame::SetTornado(
		startLoc.x,
		startLoc.y,
		TethysGame::GetRand(45) + 5,
		endLoc.x,
		endLoc.x,
		false);
}

// Losely based on Blackbox's Plymouth Cold War disaster setup.
void CreateRandomDisaster(const std::vector<LOCATION> &criticalBuildingLocations)
{
	//Set a disaster. This uses a weighted random. Picking a random number 0 to 100:
	//0-19 = no action
	//20-69 = meteor
	//70-84 = quake
	//85-94 = electrical storm
	//95-100 = vortex

	int randNum = TethysGame::GetRand(100);

	if (randNum < 15)
	{
		// No Disaster this cycle
		return;
	}
	if (randNum < 50)
	{
		CreateMeteor(criticalBuildingLocations);
	}
	else if (randNum < 70)
	{
		CreateEarthquake();
	}
	else if (randNum < 90)
	{
		CreateStorm();
	}
	else
	{
		CreateVortex();
	}
}