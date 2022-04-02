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
	_handler = new Editor(_input, 80, 45);

	int LAST_UPDATE_TIME = SDL_GetTicks();
	int startTime = LAST_UPDATE_TIME;

	while (!_closed) {
		update(-1);
		draw();
		_closed = _closed || _input->doEventInput();
	}

	terminal_close();

	//delete _th;
	delete _input;
}

void BLTWindow::update(int elapsedTime) {
	_handler->update(elapsedTime);
}

void BLTWindow::draw() {
	terminal_bkcolor(colors::black);
	terminal_clear();
	_handler->draw(0,0);

	terminal_refresh();
}