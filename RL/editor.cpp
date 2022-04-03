#include "editor.h"

Editor::Editor(Input* input, int w, int h, const wchar_t* title) : _input(input), _w(w), _h(h) {
	_tiles.resize(_w*_h);
	_cx = -globals::tWidth / 2 + _w / 2;
	_cy = -globals::tHeight/ 2 + _h / 2;

	_outline = UIBox(_w + 2, _h + 2, L"", title);

	//def character
	_brushTile = Tile(CHAR_EMPTY, colors::black, colors::white);
}

Editor::~Editor() {
	
}

void Editor::update(int elapsedTime) {
	if (_input->isKeyHeld(TK_A))
		_cx--;
	if (_input->isKeyHeld(TK_D))
		_cx++;
	if (_input->isKeyHeld(TK_W))
		_cy--;
	if (_input->isKeyHeld(TK_S))
		_cy++;
}

void Editor::draw() {
	terminal_bkcolor(colors::black);
	terminal_clear();

	//the outline UIBox
	_outline.draw(-_cx - 1, -_cy - 1);

	//the drawable area
	for (int j = 0; j < _h; j++) {
		for (int i = 0; i < _w; i++) {
			drawSingleTile(i - _cx, j - _cy, &_tiles[i + j * _w]);
		}
	}

	//mouse code.
	{
		int mx, my;
		_input->getMousePos(&mx, &my);

		if (_input->isKeyHeld(TK_MOUSE_LEFT)) {
			//_tiles[mx + my * _w].bgcolor = colors::indexed[_color];
			storeSingleTile(mx + _cx, my + _cy, &_brushTile);
		}
		if (_input->isKeyHeld(TK_MOUSE_RIGHT)) {
			_brushTile = getTile(mx + _cx, my + _cy);
		}
		//if (_input->isKeyPressed(TK_SPACE)) {
		//	_state = EDITOR_STATE_PICKER;
		//}
		//the preview char on cursor
		terminal_layer(0);
		terminal_color(_brushTile.fgcolor);
		terminal_bkcolor(_brushTile.bgcolor);
		terminal_put(mx, my, _brushTile.character);
		

		// cursor drawing code.consider abstracting for arbitrary cursor styles
		terminal_layer(1);
		terminal_color(colors::white);
		terminal_put(mx + 1, my, L']');
		terminal_put(mx - 1, my, L'[');
	}
	terminal_layer(0);
	terminal_refresh();
}

void Editor::drawSingleTile(int x, int y, Tile* tile) {   
	terminal_bkcolor(tile->bgcolor);
	terminal_color(tile->fgcolor);
	terminal_put(x, y, tile->character);
}

bool Editor::areValidCoords(int x, int y) {
	if (x < 0 || y < 0 || x > _w - 1 || y > _h - 1) {
		//printf("invalid loc\n");
		return false;
	}
	return true;
}

bool Editor::storeSingleTile(int x, int y, Tile* tile) {
	if (!areValidCoords(x, y))
		return false;
	_tiles[x + y * _w] = *tile;
	return true;
}

Tile Editor::getTile(int x, int y) {
	if (!areValidCoords(x, y))
		return Tile();
	return _tiles[x + y * _w];
}