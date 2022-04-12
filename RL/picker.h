#pragma once
#include "uibox.h"
#include "colors.h"
#include "geometric character points.h"
#include "tile.h"
#include "input.h"

#define COLPICKER_WIDTH 4
#define COLPICKER_OFFS_X -COLPICKER_WIDTH - 2
#define COLPICKER_OFFS_Y -3

#define CHARPICKER_WIDTH 16
#define CHARPICKER_HEIGHT 6
#define CHARPICKER_OFFS_X 4
#define CHARPICKER_OFFS_Y -CHARPICKER_HEIGHT / 2

// unique color/char picker for editor
class Picker {
public:
	Picker(Tile* currtile, Input* input);
	~Picker();

	void update(int mxl, int myl);
	void draw(int x, int y);
private:
	UIBox _colbox;
	UIBox _charbox;
	Tile* _currTile;
	int _colw, _colh;
	Input* _input;
};