#pragma once
#include "tile.h"

struct Voxel {
	Voxel(Tile* top = &Tile(u'�Z'), Tile* side = &Tile(u'��'));

	Tile topTile, sideTile;
};