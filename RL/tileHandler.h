#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include "globals.h"
#include "tile.h"

class TileHandler {
public:
	TileHandler(const std::string fontPath, int fontSize);
	//def need a destructor to clear the spritesheet
	void draw();
	
	SDL_Texture* getSprite(Uint16 character);
private:
	static TTF_Font* loadFont(const std::string fontPath, int fontSize);
	SDL_Texture* loadTextTexture(Uint16 character);

	Tile _tiles[globals::tWidth][globals::tHeight];
	int _w, _h, _size;
	TTF_Font* _font;
	SDL_Rect _textRect;
	std::map<Uint16, SDL_Texture*> _spriteSheet;
};