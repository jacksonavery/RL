#include "tile.h"
#include "colors.h"

Tile::Tile() {
	fgcolor = cols::white;
	bgcolor = cols::black;
	character = (Uint16) u'�E';
}
Tile::Tile(Uint16 character, SDL_Color fgcolor, SDL_Color bgcolor) :
	fgcolor(fgcolor), bgcolor(bgcolor), character(character) {}
