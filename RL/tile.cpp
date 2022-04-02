#include "tile.h"

Tile::Tile() {
	character = CHAR_EMPTY;
	fgcolor = colors::dkgray;
	bgcolor = colors::black;
}

Tile::Tile(int character, color_t fgcolor, color_t bgcolor) :
	fgcolor(fgcolor), bgcolor(bgcolor), character(character) {}
