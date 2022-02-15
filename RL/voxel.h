#pragma once
#include "tile.h"

struct Voxel {
	Voxel(Tile* top = &Tile(u'Åú'), Tile* side = &Tile(u'ÅZ'));

	Tile topTile, sideTile;
};