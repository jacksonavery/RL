#pragma once
#include <vector>
#include "uibox.h"
#include "colors.h"
#include "geometric character points.h"
#include "tile.h"
#include "input.h"
#include "globals.h"

#define COLPICKER_WIDTH 5
#define COLPICKER_OFFS_X -COLPICKER_WIDTH - 2
#define COLPICKER_OFFS_Y -3

#define CHARPICKER_WIDTH 16
#define CHARPICKER_HEIGHT 16
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
	void advanceCharPickerOffset();

	UIBox _colbox;
	UIBox _charbox;
	int _charpointindex;
	std::vector<int> _charpointoffsets = {0, 0x0370, 0x25A0, 0x2600, 0xE000};
	Tile* _currTile;
	int _colw, _colh;
	Input* _input;
};