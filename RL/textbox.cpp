#include "textbox.h"
#include "tileHandler.h"

TextBox::TextBox(const char16_t* string, int xin, int yin, int win, int hin) {
	x = xin, y = yin, w = win, h = hin;
	data = new Tile[win*hin];
	Tile a(u' ', SDL_Color{255, 255, 255, 255}, SDL_Color{ 0, 0, 0, 255 });
	for (int i = 0; i < win*hin; i++) {
		data[i] = a;
	}
	TileHandler::makeStringNaive(string, data, 1, 1, win-2, hin-2, win, hin);
}

TextBox::~TextBox() {
	delete[] data;
}
