#pragma once
#include "tile.h"

struct Voxel {
	Voxel(Tile* top = &Tile(u'��'), Tile* side = &Tile(u'�T'));

	Tile topTile, sideTile;
};