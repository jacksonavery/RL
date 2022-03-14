#include "BLTwindow.h"

#include <algorithm>
#include "globals.h"

BLTWindow::BLTWindow(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height) {
	if (!init())
		terminal_close();

	gameLoop();
}

BLTWindow::~BLTWindow() {
	//ç°ÇµÇ»Ç¢
}

bool BLTWindow::init() {
	//std::cout << "opening\n";
	if (!terminal_open())
		return false;
	if (!terminal_set("window: title='3', size = 80x45"))
		return false;
	if (!terminal_set("font: fonts/bitmap/nanahyakumanji.png, size=8x8"))
		return false;
	//terminal_set("font: fonts/LucidaTypewriterRegular.ttf, size = 16");
	return true;
}

void BLTWindow::gameLoop() {
	//std::cout << "starting loop\n";
	_input = new Input();
	//_th = new TileHandler(globals::font, globals::tileSize, _input);

	while (!_closed) {
		//std::cout << "looping\n";
		draw();
		
		_closed = _input->doEventInput();
	}

	terminal_close();

	//delete _th;
	delete _input;
}

void BLTWindow::draw() {
	//std::cout << "drawing\n";
	terminal_print(1, 1, "when the soulja boy is cranked");
	terminal_refresh();
}