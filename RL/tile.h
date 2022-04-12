#pragma once
#include <BearLibTerminal.h>
#include "colors.h"
#include "geometric character points.h"

struct Tile {
	Tile();
	Tile(int character, int fgcolor, int bgcolor);

	int fgcolor, bgcolor;
	int character;
};