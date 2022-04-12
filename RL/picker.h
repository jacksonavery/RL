#pragma once
#include "uibox.h"
#include "colors.h"
#include "geometric character points.h"
#include "tile.h"
#include "input.h"

#define CPICKER_WIDTH 6
#define CPICKER_OFFS_X -3
#define CPICKER_OFFS_Y -2

// unique color/char picker for editor
class Picker {
public:
	Picker(Tile* currtile, Input* input);
	~Picker();

	void update(int mxl, int myl);
	void draw(int x, int y);
private:
	UIBox _uibox;
	Tile* _currTile;
	int _w, _h;
	Input* _input;
};