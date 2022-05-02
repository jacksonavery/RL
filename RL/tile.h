#pragma once
#include <BearLibTerminal.h>
#include "colors.h"
#include "geometric character points.h"

struct Tile {
	Tile();
	Tile(int character, int fgcolor, int bgcolor);

	int fgcolor, bgcolor;
	int character;

	bool operator==(const Tile& other) {
		if (fgcolor != other.fgcolor)
			return false;
		if (bgcolor != other.bgcolor)
			return false;
		if (character != other.character)
			return false;
		return true;
	}
};