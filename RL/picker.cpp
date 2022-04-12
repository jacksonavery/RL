#include "picker.h"

Picker::Picker(Tile* currtile, Input* input) : _currTile(currtile), _input(input) {
	_colw = COLPICKER_WIDTH;
	_colh = (colors::numcolors + COLPICKER_WIDTH - 1) / COLPICKER_WIDTH;
	_colbox = UIBox(_colw + 2, _colh + 2, L"", L"cols");

	_charbox = UIBox(CHARPICKER_WIDTH + 2, CHARPICKER_HEIGHT + 2, L"", L"chars");
}

Picker::~Picker() {
	return;
}

void Picker::update(int mxl, int myl) {
	// ==color box==
	mxl -= COLPICKER_OFFS_X + 1;
	myl -= COLPICKER_OFFS_Y + 1;
	if (_input->isKeyPressed(TK_MOUSE_LEFT))
		if (mxl < _colw && mxl >= 0 && myl >= 0 && mxl + myl * _colw < colors::numcolors)
			_currTile->fgcolor = mxl + myl * _colw;
	if (_input->isKeyPressed(TK_MOUSE_RIGHT))
		if (mxl < _colw && mxl >= 0 && myl >= 0 && mxl + myl * _colw < colors::numcolors)
			_currTile->bgcolor = mxl + myl * _colw;
	// ==chars box==
	// TODO: this can't be right but it works atm
	mxl += COLPICKER_OFFS_X - CHARPICKER_OFFS_X + 4;
	myl += COLPICKER_OFFS_Y - CHARPICKER_OFFS_Y;
	if (_input->isKeyPressed(TK_MOUSE_LEFT))
		if (mxl < CHARPICKER_WIDTH && mxl >= 0 && myl >= 0 && myl < CHARPICKER_HEIGHT)
			_currTile->character = 0xE000 + mxl + myl * CHARPICKER_WIDTH;
}

void Picker::draw(int x, int y) {
	// ==color box==
	x += COLPICKER_OFFS_X;
	y += COLPICKER_OFFS_Y;
	_colbox.draw(x, y);
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
		terminal_put(x + 1 + i % _colw, y + 1 + i / _colw, currchar);
	}
	// ==char box==
	x += CHARPICKER_OFFS_X - COLPICKER_OFFS_X;
	y += CHARPICKER_OFFS_Y - COLPICKER_OFFS_Y;
	_charbox.draw(x, y);
	terminal_bkcolor(colors::indexed[_currTile->bgcolor]);
	terminal_color(colors::indexed[_currTile->fgcolor]);
	for (int i = 0; i < CHARPICKER_WIDTH * CHARPICKER_HEIGHT; i++) {
		terminal_put(x + 1 + i % CHARPICKER_WIDTH, y + 1 + i / CHARPICKER_WIDTH, 0xE000+i);
	}
}