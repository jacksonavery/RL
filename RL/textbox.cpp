#include "textbox.h"
#include "tileHandler.h"

TextBox::TextBox(const char16_t* string, int xin, int yin, int win, int hin) {
	x = xin, y = yin, w = win, h = hin;
	data = new Tile[win*hin];
	
	//make box
	TileHandler::makeBoundingBox(data, x, y, w, h);
	//make string
	TileHandler::makeStringNaive(string, data, 1, 1, win-2, hin-2, win, hin);
}

TextBox::~TextBox() {
	delete[] data;
}
