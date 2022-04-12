#include "tile.h"

Tile::Tile() {
	character = CHAR_EMPTY;
	fgcolor = 1;
	bgcolor = 0;
}

Tile::Tile(int character, int fgcolor, int bgcolor) :
	fgcolor(fgcolor), bgcolor(bgcolor), character(character) {}
