#pragma once
#include <BearLibTerminal.h>

struct Tile {
	Tile(uint16_t character, color_t fgcolor = color_from_argb(255, 255, 255, 255), color_t bgcolor = color_from_argb(0, 0, 0, 255));

	color_t fgcolor, bgcolor;
	uint16_t character;
};