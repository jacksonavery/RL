#include "tile.h"
#include "colors.h"


//Tile::Tile(Uint16 character, SDL_Color fgcolor, SDL_Color bgcolor) :
//	fgcolor(fgcolor), bgcolor(bgcolor) {
//	setChar(character);
//}

Tile::Tile(bool shouldYouBeDoingThis) {
	if (!shouldYouBeDoingThis)
		throw;
}