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
	//movement.
	if (_input->isKeyHeld(TK_MOUSE_MIDDLE)) {
		bool pressed = false;
		doMMBMove();
	}
	
	//mouse pencil. TODO: refactor to updatePencil and so on (prob updateTool(), which will get _currtool)
	_input->getMousePos(&_mx, &_my);

	if (_input->isKeyHeld(TK_MOUSE_LEFT)) {
		storeSingleTile(_mx + _cx, _my + _cy, &_brushTile);
	}
	if (_input->isKeyHeld(TK_MOUSE_RIGHT)) {
		_brushTile = getTile(_mx + _cx, _my + _cy);
	}
}

void Editor::draw() {
	//the outline UIBox
	_outline.draw(-_cx - 1, -_cy - 1);

	//the drawable area
	for (int j = 0; j < _h; j++) {
		for (int i = 0; i < _w; i++) {
			drawSingleTile(i - _cx, j - _cy, &_tiles[i + j * _w]);
		}
	}

	//the preview char on cursor. TODO: move into drawPencil or however
	_input->getMousePos(&_mx, &_my);
	if (areValidCoords(_mx + _cx, _my + _cy)) {
		terminal_layer(0);
		terminal_color(_brushTile.fgcolor);
		terminal_bkcolor(_brushTile.bgcolor);
		terminal_put(_mx, _my, _brushTile.character);
	}
	
	// cursor drawing code. TODO: abstracting for arbitrary cursor styles
	terminal_layer(1);
	terminal_color(colors::white);
	terminal_put(_mx + 1, _my, L']');
	terminal_put(_mx - 1, _my, L'[');

	terminal_layer(0);
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

void Editor::doMMBMove() {
	//set past coords on original MMB press
	if (_input->isKeyPressed(TK_MOUSE_MIDDLE)) {
		_fmx = _mx;
		_fmy = _my;
		_fcx = _cx;
		_fcy = _cy;
	}
	//update based on current MMB pos
	_cx = _fcx + _fmx - _mx;
	_cy = _fcy + _fmy - _my;
}