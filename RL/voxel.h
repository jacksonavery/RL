#pragma once
#include "tile.h"

struct Voxel {
	Voxel(Tile* top = &Tile(u'Мы'), Tile* side = &Tile(u'ЯT'));

	Tile topTile, sideTile;
};