#pragma once

#include "HFL\Source\HFL.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

namespace AIHelper
{
	bool IsTubeOrWall(map_id type);
	void RecordTubeOrWallHorizLine(BuildingGroup &buildingGroup, int x1, int x2, int y, map_id type);
	void RecordTubeOrWallVertLine(BuildingGroup &buildingGroup, int y1, int y2, int x, map_id type);
	void RecordTubeOrWallLine(BuildingGroup &buildingGroup, int x1, int y1, int x2, int y2, map_id type);
	bool SearchForBuildingToRepair(UnitEx &repairVech, int playerNumber, int damageThreshold, map_id structTypeToRepair);
	void SearchForBuildingToRepair(UnitEx &repairVech, int playerNumber, int damageThreshold, const std::vector<map_id> &structureTypesToRepair);
}