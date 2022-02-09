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
	
	//loads a sprite if it's hasnt been loaded yet. then returns a pointer to it
	SDL_Texture* getSprite(Uint16 character);
	//breaks a string down into the world
	void drawString(const char16_t* string, int x, int y, int w = 0, int h = 0, bool smartWordCut = false);
private:
	//loads a font and sets it
	static TTF_Font* loadFont(const std::string fontPath, int fontSize);
	//actually loads the sprite texture
	SDL_Texture* loadTextTexture(Uint16 character);

	Tile _tiles[globals::tWidth][globals::tHeight];
	int _w, _h, _size;
	TTF_Font* _font;
	SDL_Rect _textRect;
	std::map<Uint16, SDL_Texture*> _spriteSheet;
};