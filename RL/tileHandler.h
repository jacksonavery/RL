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

	//updater
	void update(int elapsedTime);
	//calls all draws
	void draw();
	
	//loads a sprite if it's hasnt been loaded yet. then returns a pointer to it
	SDL_Texture* getSprite(Uint16 character);

	static void initTileSetTiles(std::vector<std::vector<Tile>>* destTileSet, int w, int h);
	//breaks a string down into the world
	static void makeStringNaive(const char16_t* string, std::vector<std::vector<Tile>>* destTileSet, int x, int y, int w, int h);
	//fills a layer with a box **EXPECTS TO FILL THE WHOLE LAYER, WILL NOT FUNCTION CORRECTLY OTHERWISE**
	static void makeBoundingBox(std::vector<std::vector<Tile>>* destTileSet, int x, int y, int w, int h);
private:
	//loads a font and sets it
	static TTF_Font* loadFont(const std::string fontPath, int fontSize);
	//actually loads the sprite texture
	SDL_Texture* loadTextTexture(Uint16 character);
	//draws an actual set of tiles
	void drawTileSet(std::vector<std::vector<Tile>>* tileset, int x = 0, int y = 0);

	std::vector<std::vector<Tile>> _bgTiles;
	std::vector<Popup*> _popups;
	int _w = globals::tWidth, _h = globals::tHeight;
	TTF_Font* _font;
	SDL_Rect _textRect;
	std::map<Uint16, SDL_Texture*> _spriteSheet;
};