#include "picker.h"

Picker::Picker(Tile* currtile, Input* input) : _currTile(currtile), _input(input) {
	_w = PICKER_WIDTH;
	_h = (colors::numcolors + PICKER_WIDTH - 1) / PICKER_WIDTH;
	_uibox = UIBox(_w + 2, _h + 2, L"", L"colors");
}

Picker::~Picker() {
	return;
}

void Picker::update(int mxl, int myl) {
	mxl--, myl--;
	if (_input->isKeyPressed(TK_MOUSE_LEFT))
		if (mxl + myl * PICKER_WIDTH < colors::numcolors)
			_currTile->fgcolor = mxl + myl * PICKER_WIDTH;
	if (_input->isKeyPressed(TK_MOUSE_RIGHT))
		if (mxl + myl * PICKER_WIDTH < colors::numcolors)
			_currTile->bgcolor = mxl + myl * PICKER_WIDTH;
}

void Picker::draw(int x, int y) {
	x -= PICKER_WIDTH + 2;
	y -= 2;
	//draw bg box
	_uibox.draw(x, y);
	//add colors
	for (int i = 0; i < colors::numcolors; i++) {
		int currchar = CHAR_EMPTY;
		terminal_bkcolor(colors::indexed[i]);
		terminal_color(colors::indexed[(i+1)%colors::numcolors]);
		//ugly but just highlights which is fg and bg
		if (i == _currTile->fgcolor) {
			if (i == _currTile->bgcolor)
				currchar = L'2';
			else
				currchar =  L'f';
		}
		else if (i == _currTile->bgcolor) {
			currchar = L'b';
		}

		terminal_put(x + 1 + i % PICKER_WIDTH, y + 1 + i / PICKER_WIDTH, currchar);
	}
}