#include "MapHelper.h"

namespace MapHelper
{
	void SetLavaPossibleRegion(const MAP_RECT &mapRect)
	{
		int rectWidth = mapRect.x2 - mapRect.x1 + 1;
		int rectHeight = mapRect.y2 - mapRect.y1 + 1;
		int numberOfTiles = rectWidth * rectHeight;

		LOCATION currentLoc;
		for (int i = 0; i < numberOfTiles; ++i)
		{
			currentLoc = LOCATION(mapRect.x1 + i % rectWidth, mapRect.y1 + i / rectWidth);
			GameMap::SetLavaPossible(currentLoc, true);
		}
	}

	void SetLavaPossibleAllSlowCells(MAP_RECT mapRect)
	{
		int x, y, tile;

		for (y = mapRect.y1; y < mapRect.y2; ++y)
		{
			for (x = mapRect.x1; x < mapRect.x2; ++x)
			{
				tile = GameMap::GetCellType(LOCATION(x, y));
				if ((tile == CellTypes::cellSlowPassible1) ||
					(tile == CellTypes::cellSlowPassible2))
				{
					GameMap::SetLavaPossible(LOCATION(x, y), true);
				}
			}
		}
	}

	void SetSouthEastLavaFlowAni(LOCATION location)
	{
		GameMap::SetTile(LOCATION(location.x, location.y), 0x489);
		GameMap::SetTile(LOCATION(location.x, location.y + 1), 0x4A0);
		GameMap::SetTile(LOCATION(location.x + 1, location.y + 1), 0x4AB);
		GameMap::SetTile(LOCATION(location.x + 1, location.y), 0x494);
	}

	void CreateFumaroleInRegion(MAP_RECT mapRect)
	{
		LOCATION fumaroleLoc = mapRect.RandPt();
		TethysGame::CreateBeacon(map_id::mapFumarole, fumaroleLoc.x, fumaroleLoc.y, -1, -1, -1);
	}

	void CreateFumarolesFromRandomLocs(size_t numberOfFumaroles, std::vector<LOCATION> locations)
	{
		if (numberOfFumaroles > locations.size())
		{
			throw "Error";
		}

		int locationIndex;
		LOCATION loc;
		for (size_t i = 0; i < numberOfFumaroles; ++i)
		{
			locationIndex = TethysGame::GetRand(locations.size());
			loc = locations[locationIndex];

			TethysGame::CreateBeacon(map_id::mapFumarole, loc.x, loc.y, -1, -1, -1);

			//TODO: Remove location from vector
		}
	}
}