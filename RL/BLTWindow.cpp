#include "BLTwindow.h"

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

	terminal_color(colors::rust);
	//printf("%d\n%d\n\n", colors::black);
	terminal_print_ext(0, 21, 80, 0, TK_ALIGN_CENTER, L"[font=sc]Inpartio Aeris[/font]");
	terminal_print_ext(0, 22, 80, 0, TK_ALIGN_CENTER, L"インパーティオ アエリス");
	terminal_print_ext(0, 25, 80, 0, TK_ALIGN_CENTER, L"all my [font=sc]friends[/font] are watching i can hear them talking");

	//auto a = L"[font=sc]Plasma Refibrilator[/font]";
	//auto b = L"[font=pc][color=red]Opponent[/font][/color] must [font=pc][color=blue]spend a turn[/font][/color] restarting their heart. Or whatever it is they've got.";
	//
	//UIBox box(40, 20, 25, 6, b, a);
	
	//mouse code
	{
		int x, y;
		_input->getMousePos(&x, &y);
		terminal_color(colors::white);
		if (_input->isKeyHeld(TK_MOUSE_LEFT))
			terminal_color(colors::lblue);
		if (_input->isKeyHeld(TK_MOUSE_RIGHT))
			terminal_color(colors::rust);
		terminal_put(x, y+1, L'^');
		if (y == globals::tHeight-1)
			terminal_put(x, y - 1, L'v');
	}

	terminal_refresh();
}