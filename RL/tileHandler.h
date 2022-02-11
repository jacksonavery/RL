#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <vector>
#include "globals.h"
#include "tile.h"
#include "popup.h"

class TileHandler {
public:
	TileHandler(const std::string fontPath, int fontSize);
	~TileHandler();
	//calls all draws
	void draw();
	
	//loads a sprite if it's hasnt been loaded yet. then returns a pointer to it
	SDL_Texture* getSprite(Uint16 character);
	//breaks a string down into the world
	//static void makeString(const char16_t* string, Tile* destTileSet, int x = 0, int y = 0, int w = 0, int h = 0, bool smartWordCut = false);
	static void makeStringNaive(const char16_t* string, Tile* destTileSet, int x, int y, int w, int h, int textw, int texth);
private:
	//loads a font and sets it
	static TTF_Font* loadFont(const std::string fontPath, int fontSize);
	//actually loads the sprite texture
	SDL_Texture* loadTextTexture(Uint16 character);
	//draws an actual set of tiles
	void drawTileSet(Tile* tileset, int x = 0, int y = 0, int w = globals::tWidth, int h = globals::tHeight);

	Tile _bgTiles[globals::tWidth*globals::tHeight];
	std::vector<Popup*> _popups;
	int _w = globals::tWidth, _h = globals::tHeight;
	TTF_Font* _font;
	SDL_Rect _textRect;
	std::map<Uint16, SDL_Texture*> _spriteSheet;
};