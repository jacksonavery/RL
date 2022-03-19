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
	//¡‚µ‚È‚¢
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
		
		_closed = _input->doEventInput();
	}

	terminal_close();

	//delete _th;
	delete _input;
}

void BLTWindow::draw() {
	//all temp stuff, should just call tilehandler's draws
	for (int i = 0; i < 80 * 45; i++) {
		terminal_put(i % 80, i / 80, '.');
	}
	terminal_print(10, 10, L"ƒl\nƒA");
	for (int i = 0; i < 96; i++) {
		terminal_put(i % 16, i / 16, L'ƒA' - 2 + i);
	}

	wchar_t aaa[] = L"=[font=sc]Plasma Refibrilator[/font]=";
	wchar_t bbb[] = L"Opponent must spend a turn restarting their heart. Or whatever it is.";
	//toSC(aaa);
	terminal_print(19, 20, aaa);
	terminal_print_ext(19, 21, 22, 0, 0, bbb);
	terminal_print(20, 20, L"[font=sc]The Terminal Do be Supporting Smallcaps Tho[/font]");

	terminal_refresh();
}