#include "editor.h"

Editor::Editor(Input* input, int w, int h, const wchar_t* title) : _input(input), _w(w), _h(h) {
	_tiles.resize(_w*_h);
	_cx = -globals::tWidth / 2 + _w / 2;
	_cy = -globals::tHeight/ 2 + _h / 2;

	_outline = UIBox(_w + 2, _h + 2, L"", title);

	//def character
	_brushTile = Tile(CHAR_EMPTY, 0, 1);
	//picker
	_picker = new Picker(&_brushTile, _input);
	//no windows open by def
	_state = states::direct;
}

Editor::~Editor() {
	delete(_picker);
}

void Editor::update(int elapsedTime) {
	//only allows current 'state' to get input
	switch (_state) {
	case states::direct:
		doDirectInput();
		break;
	case states::picker:
		doPicker();
		break;
	default:
		printf("Editor: Unrecognized state %d", _state);
		_state = states::direct;
		break;
	}
}

void Editor::doDirectInput() {
	//enter picker mode
	if (_input->isKeyPressed(TK_SPACE)) {
		_state = states::picker;
		_px = _mx;
		_py = _my;
		return;
	}
	//movement.
	if (_input->isKeyHeld(TK_MOUSE_MIDDLE)) {
		doMMBMove();
	}
	//invert currtile
	if (_input->isKeyPressed(TK_F)) {
		auto a = _brushTile.bgcolor;
		_brushTile.bgcolor = _brushTile.fgcolor;
		_brushTile.fgcolor = a;
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

//Todo
void Editor::doPicker() {
	//leave picker mode
	if (_input->isKeyPressed(TK_SPACE)) {
		_state = states::direct;
		return;
	}
	//give relative mouse coords to the picker
	_picker->update(_mx - _px, _my - _py);
}

void Editor::draw() {
	//draw bg
	drawDirect();
	//draw any windows
	switch (_state) {
	case states::picker:
		drawPicker();
		break;
	}
	//draw cursor
	drawCursor();
}

void Editor::drawDirect() {
	//the outline UIBox
	_outline.draw(-_cx - 1, -_cy - 1);

	//the drawable area
	for (int j = 0; j < _h; j++) {
		for (int i = 0; i < _w; i++) {
			drawSingleTile(i - _cx, j - _cy, &_tiles[i + j * _w]);
		}
	}
}

void Editor::drawPicker() {
	_picker->draw(_px, _py);
}

void Editor::drawCursor() {
	//the preview char on cursor. TODO: move into drawPencil or however
	_input->getMousePos(&_mx, &_my);
	if (areValidCoords(_mx + _cx, _my + _cy, _w, _h) && _state == states::direct) {
		terminal_layer(0);
		terminal_color(colors::indexed[_brushTile.fgcolor]);
		terminal_bkcolor(colors::indexed[_brushTile.bgcolor]);
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
	terminal_bkcolor(colors::indexed[tile->bgcolor]);
	terminal_color(colors::indexed[tile->fgcolor]);
	terminal_put(x, y, tile->character);
}

bool Editor::areValidCoords(int x, int y, int w, int h) {
	if (x < 0 || y < 0 || x > w - 1 || y > h - 1) {
		//printf("invalid loc\n");
		return false;
	}
	return true;
}

bool Editor::storeSingleTile(int x, int y, Tile* tile) {
	if (!areValidCoords(x, y, _w, _h))
		return false;
	_tiles[x + y * _w] = *tile;
	return true;
}

Tile Editor::getTile(int x, int y) {
	if (!areValidCoords(x, y, _w, _h))
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