#pragma once
#include <SDL_ttf.h>

struct Tile {
	//should not be called directly
	Tile(bool shouldYouBeDoingThis = false);
	//Tile(Uint16 character = u'ÅE', SDL_Color fgcolor = SDL_Color{255, 255, 255, 255}, SDL_Color bgcolor = SDL_Color{ 0, 0, 0, 255 });

	SDL_Color fgcolor, bgcolor;
	void setChar(Uint16 character);
	Uint16 getChar(Uint16 character);
	SDL_Texture* getSprite(Uint16 character);
private:
	SDL_Texture* _sprite;
	Uint16 _character;
};