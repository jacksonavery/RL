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
	//load default font (page 437)
	if (!terminal_set("font: fonts/bitmap/7tkji-basic.png, size=8x8, codepage=437"))
		return false;
	//katakana
	if (!terminal_set("0x30a0: fonts/bitmap/7tkji-katakana.png, size=8x8"))
		return false;
	//misc symbols
	if (!terminal_set("0x2600: fonts/bitmap/7tkji-misc-sym.png, size=8x8"))
		return false;
	//variant fonts
	//  TODO: make this work
	//if (!terminal_set("0x61: fonts/bitmap/7tkji-sc.png, size=8x8"))
	//	return false;

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
	//std::cout << "drawing\n";

	//all temp stuff, should just call tilehandler's draws
	for (int i = 0; i < 80 * 45; i++) {
		terminal_put(i % 80, i / 80, '.');
	}
	terminal_print(10, 10, L"ƒl\nƒA");
	terminal_print(12, 12, L"[font = sc]Plasma Refibrilator[/font]");
	terminal_print(12, 13, L"Opponent must rest \none turn in order  \nto restart their   \nheart.             ");
	terminal_refresh();
}