#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <vector>
#include "globals.h"
#include "input.h"
#include "tile.h"
#include "voxel.h"
#include "popup.h"

class TileHandler {
public:
	TileHandler(const std::string fontPath, int fontSize, Input* input);
	~TileHandler();

	//updater
	void update(int elapsedTime);
	//calls all draws
	void draw();
	
	//loads a sprite if it hasnt been loaded yet. returns a pointer to it
	SDL_Texture* getSprite(Uint16 character);
	//fills with default tiles.
	static void initTileSetTiles(std::vector<std::vector<Tile>>* destTileSet, int w, int h);
	//same with voxels
	static void initVoxelSetVoxels(std::vector<std::vector<Voxel>>* destTileSet, int w, int h);
	//breaks a string down into the world
	static void makeStringNaive(const char16_t* string, std::vector<std::vector<Tile>>* destTileSet, int x, int y, int w, int h);
	//fills a layer with a box **EXPECTS TO FILL THE WHOLE LAYER, WILL NOT FUNCTION CORRECTLY OTHERWISE**
	static void makeBoundingBox(std::vector<std::vector<Tile>>* destTileSet, bool isThick = true);
private:
	//loads a font and sets it
	static TTF_Font* loadFont(const std::string fontPath, int fontSize);
	//actually loads the sprite texture
	SDL_Texture* loadTextTexture(Uint16 character);
	//draws an actual set of tiles to int. screen
	void drawTileSetToScreen(std::vector<std::vector<Tile>>* tileset, std::vector<std::vector<Tile*>>* screen, int x = 0, int y = 0);
	//draw one tile
	void drawSingleTile(Tile* tile, int x, int y);
	//draws a set of voxels
	void drawVoxelSetToScreen(std::vector<std::vector<Voxel>>* tileset, std::vector<std::vector<Tile*>>* screen, int x = 0, int y = 0);
	//raytrace draw
	void drawRTToScreen(std::vector<std::vector<Tile*>>* screen);
	//actually draws screen to window
	void drawScreen(std::vector<std::vector<Tile*>>* screen);


	//update camera pos
	void doCameraMovement(int elapsedTime);

	std::vector<std::vector<Tile>> _bgTiles;
	std::vector<std::vector<Voxel>> _voxels;
	std::vector<std::vector<std::vector<Voxel>>> _elevations;
	std::vector<Popup*> _popups;

	std::vector<std::vector<Tile*>> _screen;


	TTF_Font* _font;
	SDL_Rect _textRect;
	std::map<Uint16, SDL_Texture*> _spriteSheet;

	Input* _input;

	int _camerax, _cameray, _camerar, _camerah;
	int _timeSinceLastCameraUpdate;

	Tile _zBoundTile = Tile(u'�E');
	Tile _transparentTile = Tile(0);
};