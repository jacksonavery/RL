#pragma once
#include "tile.h"

struct Voxel {
	Voxel(Tile* top = &Tile(0x25A1), Tile* side = &Tile(0x5182));

	Tile topTile, sideTile;
};