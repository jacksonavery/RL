#include "voxel.h"

Voxel::Voxel(Tile* top, Tile* side) {
	topTile = *top;
	sideTile = *side;
}