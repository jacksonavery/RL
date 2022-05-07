#pragma once
#include <vector>
#include "tile.h"

struct coordHelper {
	// returns whether given coords are within given bounds
	static bool areValidCoords(int x, int y, int w, int h);
	// return a square subset of a set of tiles. error checks. tw and th are of the initial tileset.
	// returns an empty vector on failure.
	static std::vector<Tile*> getSubset(int x, int y, int w, int h, std::vector<Tile>* tiles, int tw, int th);
};