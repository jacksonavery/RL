#pragma once
#include <vector>
#include <BearLibTerminal.h>
#include "tile.h"
#include "input.h"

class Editor {
public:
	Editor(Input* input, int w, int h);
	~Editor();
	void update(int elapsedTime);
	void draw(int xoff, int yoff);
private:
	void drawSingleTile(int x, int y, Tile* tile);
	std::vector<Tile> _tiles;
	Input* _input;
	int _w, _h;
};