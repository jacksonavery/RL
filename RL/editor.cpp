#include "editor.h"

Editor::Editor(Input* input, int w, int h) : _input(input), _w(w), _h(h) {
	_tiles.resize(_w*_h);
}

Editor::~Editor() {
	
}

void Editor::update(int elapsedTime) {

}

void Editor::draw(int x, int y) {
	for (int j = 0; j < _h; j++) {
		for (int i = 0; i < _w; i++) {
			drawSingleTile(x + i, y + j, &_tiles[i + j * _w]);
		}
	}
	//mouse code
	{
		terminal_bkcolor(colors::black);
		int x, y;
		_input->getMousePos(&x, &y);
		terminal_color(colors::indexed[15]);
		if (_input->isKeyHeld(TK_MOUSE_LEFT)) {
			terminal_color(colors::lblue);
			_tiles[x + y * _w].character = CHAR_FULL;
		}
		if (_input->isKeyHeld(TK_MOUSE_RIGHT)) {
			terminal_color(colors::rust);
			_tiles[x + y * _w].character = CHAR_EMPTY;
		}
		terminal_put(x + 1, y, L']');
		terminal_put(x - 1, y, L'[');
	}
}

void Editor::drawSingleTile(int x, int y, Tile* tile) {
		terminal_bkcolor(tile->bgcolor);
		terminal_color(tile->fgcolor);
		terminal_put(x, y, tile->character);
}