#include "BLTwindow.h"

#include <algorithm>
#include "globals.h"
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
	terminal_clear();

	//for (int i = 0; i < 80 * 45; i++) {
	//	terminal_put(i % 80, i / 80, '.');
	//}
	//terminal_print(10, 10, L"ネ\nア");
	//for (int i = 0; i < 96; i++) {
	//	terminal_put(i % 16, i / 16, L'ア' - 2 + i);
	//}
	//
	//wchar_t aaa[] = L"=[font=sc]Plasma Refibrilator[/font]=";
	//wchar_t bbb[] = L"Opponent must spend a turn restarting their heart. Or whatever it is.";
	////toSC(aaa);
	//terminal_print(19, 20, aaa);
	//terminal_print_ext(19, 21, 22, 0, 0, bbb);
	//
	//wchar_t str[] = L"[font=sc]nanahyakuman[/font]";
	//terminal_print_ext(0, 20, 80, 0, TK_ALIGN_CENTER, str);
	//terminal_print_ext(0, 21, 80, 0, TK_ALIGN_CENTER, L"ナ ナ ヒャ ク マ ン");

	//for (int i = 0; i < 80 * 45; i++) {
	//	terminal_bkcolor("#FF00FF");
	//}

	//terminal_layer(0);
	//for (int i = 0; i < 80 * 45; i++) {
	//	terminal_bkcolor( colmix(colmix(red,blu, 1.0f*(i%80)/80), grn, 1.0f*(i/80)/80));
	//	terminal_put(i % 80, i / 80, L' ');
	//}
	//terminal_layer(1);
	//terminal_bkcolor(red);
	terminal_color("white");
	terminal_print_ext(0, 21, 80, 0, TK_ALIGN_CENTER, L"[font=sc]Inpartio Aeris[/font]");
	terminal_print_ext(0, 22, 80, 0, TK_ALIGN_CENTER, L"インパーティオ アエリス");
	//printf("%d\n", L'・');

	//auto a = L"[font=sc]Plasma Refibrilator[/font]";
	//auto b = L"[font=pc][color=red]Opponent[/font][/color] must [font=pc][color=blue]spend a turn[/font][/color] restarting their heart. Or whatever it is they've got.";
	//
	//UIBox box(40, 20, 25, 6, b, a);

	//for (int i = 0; i < 16*6; i++) {
	//	terminal_put(i % 16, i / 16, 0xE000+i);
	//}
	
	//mouse code
	{
		int x, y;
		_input->getMousePos(&x, &y);
		terminal_color("white");
		if (_input->isKeyHeld(TK_MOUSE_LEFT))
			terminal_color("red");
		terminal_put(x, y+1, L'^');
		if (y == globals::tHeight-1)
			terminal_put(x, y - 1, L'v');
	}

	terminal_refresh();
}