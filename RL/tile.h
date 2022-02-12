#pragma once
#include <SDL_ttf.h>

struct Tile {
	Tile();
	Tile(Uint16 character, SDL_Color fgcolor = SDL_Color{255, 255, 255, 255}, SDL_Color bgcolor = SDL_Color{ 0, 0, 0, 255 });

	SDL_Color fgcolor, bgcolor;
	Uint16 character;
};