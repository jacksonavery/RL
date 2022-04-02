#pragma once
#include <BearLibTerminal.h>
#include "colors.h"
#include "geometric character points.h"

struct Tile {
	Tile();
	Tile(int character, color_t fgcolor, color_t bgcolor);

	color_t fgcolor, bgcolor;
	int character;
};