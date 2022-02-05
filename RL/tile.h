#pragma once
#include <SDL_ttf.h>

class Tile {
public:
	Tile();
	Tile(Uint16 character, SDL_Color fgcolor, SDL_Color bgcolor);

	SDL_Color fgcolor, bgcolor;
	Uint16 character;
};