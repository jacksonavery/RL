#pragma once
#include "tile.h"

struct Voxel {
	Voxel(Tile* top = &Tile(u'ÅZ'), Tile* side = &Tile(u'Åî'));

	Tile topTile, sideTile;
};