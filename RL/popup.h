#pragma once
#include "tile.h"
#include <vector>

struct Popup {
	int x, y, w, h;
	std::vector<std::vector<Tile>> data;
};