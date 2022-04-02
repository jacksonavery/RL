#include "window.h"

#include <algorithm>
#include "globals.h"
#include "colors.h"
#include "geometric character points.h"

BLTWindow::BLTWindow(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height) {
	if (!init())
		terminal_close();

	gameLoop();
}

BLTWindow::~BLTWindow() {
	//今しない
}

bool BLTWindow::init() {
	//open terminal
	if (!terminal_open())
		return false;
	//set window settings
	if (!terminal_setf("window: size = %dx%d", globals::tWidth, globals::tHeight))
		return false;
	return true;
}

void BLTWindow::gameLoop() {
	_input = new Input();
	//_th = new TileHandler(globals::font, globals::tileSize, _input);

	while (!_closed) {
		draw();
		
		_closed = _closed || _input->doEventInput();
	}

	terminal_close();

	//delete _th;
	delete _input;
}

void BLTWindow::draw() {
	//all temp stuff, should just call tilehandler's draws
	terminal_bkcolor(colors::black);
	terminal_clear();
	terminal_color(colors::indexed[15]);
	terminal_print_ext(20, 23, 40, 45, TK_ALIGN_CENTER, L"agraria");

	//mouse code
	{
		int x, y; 
		_input->getMousePos(&x, &y);
		terminal_color(colors::indexed[13]);
		if (_input->isKeyHeld(TK_MOUSE_LEFT))
			terminal_color(colors::lblue);
		if (_input->isKeyHeld(TK_MOUSE_RIGHT))
			terminal_color(colors::rust);
		terminal_put(x + 1, y, L']');
		terminal_put(x - 1, y, L'[');
	}

	terminal_refresh();
}