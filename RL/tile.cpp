#include "tile.h"

Tile::Tile() {
	fgcolor = SDL_Color{ 255, 255, 255, 255 };
	bgcolor = SDL_Color{ 0, 0, 0, 255 };
	character = (Uint16) u'ÉP';
}
Tile::Tile(Uint16 character, SDL_Color fgcolor, SDL_Color bgcolor) :
	fgcolor(fgcolor), bgcolor(bgcolor), character(character) {}
