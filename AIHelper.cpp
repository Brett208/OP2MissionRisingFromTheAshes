#include "AIHelper.h"

namespace AIHelper
{
	bool IsTubeOrWall(map_id type)
	{
		return
			type == mapTube ||
			type == mapWall ||
			type == mapLavaWall ||
			type == mapMicrobeWall;
	}

	void ThrowExceptionIfNotTubeOrWalls(map_id type)
	{
		if (!IsTubeOrWall(type))
		{
			throw "Type must be a tube or a wall.";//std::invalid_argument();
		}
	}

	void RecordTubeOrWallHorizLine(BuildingGroup &buildingGroup, int x1, int x2, int y, map_id type)
	{
		ThrowExceptionIfNotTubeOrWalls(type);

		bool buildTubes = type == mapTube;

		for (int i = x1; i <= x2; ++i)
		{
			LOCATION location = LOCATION(i, y);

			if (buildTubes)
			{
				buildingGroup.RecordTube(location);
			}
			else
			{
				buildingGroup.RecordWall(location, type);
			}
		}
	}

	void RecordTubeOrWallVertLine(BuildingGroup &buildingGroup, int y1, int y2, int x, map_id type)
	{
		ThrowExceptionIfNotTubeOrWalls(type);

		bool buildTubes = type == mapTube;

		for (int i = y1; i <= y2; ++i)
		{
			LOCATION location = LOCATION(x, i);

			if (buildTubes)
			{
				buildingGroup.RecordTube(location);
			}
			else
			{
				buildingGroup.RecordWall(location, type);
			}
		}
	}

	void RecordTubeOrWallLine(BuildingGroup &buildingGroup, int x1, int y1, int x2, int y2, map_id type)
	{
		// Determine which edges to draw along
		int vertEdge = x2;
		int horizEdge = y1;

		// Make sure (x1 <= x2) and (y1 <= y2)
		if (x1 > x2) { x1 ^= x2; x2 ^= x1; x1 ^= x2; }
		if (y1 > y2) { y1 ^= y2; y2 ^= y1; y1 ^= y2; }

		RecordTubeOrWallHorizLine(buildingGroup, x1, x2, horizEdge, type);
		RecordTubeOrWallVertLine(buildingGroup, y1, y2, vertEdge, type);
	}

	bool SearchForBuildingToRepair(
		UnitEx &repairVech, int playerNumber, int damageThreshold, map_id structTypeToRepair)
	{
		PlayerBuildingEnum findAllStructures(playerNumber, structTypeToRepair);
		UnitEx nextStructure;

		while (findAllStructures.GetNext(nextStructure))
		{
			if (nextStructure.GetDamage() >= damageThreshold)
			{
				repairVech.DoRepair(nextStructure);
				return true;
			}
		}

		return false;
	}

	void SearchForBuildingToRepair(
		UnitEx &repairVech, int playerNumber, int damageThreshold, const std::vector<map_id> &structureTypesToRepair)
	{
		for (map_id mapID : structureTypesToRepair)
		{
			if (SearchForBuildingToRepair(repairVech, playerNumber, damageThreshold, mapID))
			{
				return;
			}
		}
	}
}
