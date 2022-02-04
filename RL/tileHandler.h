#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "tile.h"

class TileHandler {
public:
	TileHandler(const std::string fontPath, int fontSize);
	void draw(int x, int y);
	
	static TTF_Font* loadFont(const std::string fontPath, int fontSize);
	SDL_Texture* loadTextTexture(Uint16* character);
	
private:
	Tile** _tiles;
	int _w, _h, _size;
	TTF_Font* _font;
	SDL_Rect _textRect;

	SDL_Texture* _textTexture;
};