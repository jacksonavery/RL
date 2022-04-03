#pragma once
#include <vector>
#include <BearLibTerminal.h>
#include "globals.h"
#include "tile.h"
#include "input.h"
#include "uibox.h"

class Editor {
public:
	Editor(Input* input, int w, int h, const wchar_t* title = L"untitled");
	~Editor();
	void update(int elapsedTime);
	void draw();
private:
	//returns whether given coords are within canvas bounds
	bool areValidCoords(int x, int y);
	//calls terminal_put with a tile
	void drawSingleTile(int x, int y, Tile* tile);
	//stores a tile into the vector.
	//return 0 if out of bounds.
	bool storeSingleTile(int x, int y, Tile* tile);
	//get a tile at a coordinate
	Tile getTile(int x, int y);
	
	//the current canvas
	std::vector<Tile> _tiles;
	//so we can get key status remotely
	Input* _input;
	//size of current canvas
	int _w, _h;
	//external box
	UIBox _outline;
	//the "brush"
	Tile _brushTile;
	//camera coords
	int _cx, _cy;
};