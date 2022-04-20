#include "uibox.h"

UIBox::UIBox() {
	UIBox(10, 10, L"def UIBox");
}

UIBox::UIBox(int w, int h, const wchar_t* message, const wchar_t* title, int outlinestyle) :
	_w(w - 1), _h(h - 1) {
	_message.assign(message);
	_title.assign(title);
	set_outline(outlinestyle);
}
UIBox::~UIBox() {
	//nandemo
}

void UIBox::set_outline(int outlinestyle) {
	switch (outlinestyle) {
	default:
		printf("unknown box outline style %d\n",outlinestyle);
	case UIBOX_OUTLINE_CENTERED:
		_tlcorner = CHAR_CENTERED_LINE_L_TOP_LEFT;
		_trcorner = CHAR_CENTERED_LINE_L_TOP_RIGHT;
		_blcorner = CHAR_CENTERED_LINE_L_BOTTOM_LEFT;
		_brcorner = CHAR_CENTERED_LINE_L_BOTTOM_RIGHT;
		_upper = _lower = CHAR_CENTERED_LINE_HORIZONTAL;
		_left = _right = CHAR_CENTERED_LINE_VERTICAL;
		break;
	}
}

void  UIBox::setTitle(const wchar_t* title) {
	_title.assign(title);
}

void UIBox::draw(int x, int y) {
	terminal_bkcolor(colors::black);
	terminal_color(colors::dkgray);
	//horizontals
	for (int i = 1; i < _w; i++) {
		terminal_put(x + i, y, _upper);
		terminal_put(x + i, y+_h, _lower);
	}
	//verticals
	for (int i = 1; i < _h; i++) {
		terminal_put(x, y + i, _left);
		terminal_put(x + _w, y + i, _right);
	}
	//corners
	terminal_put(x, y, _tlcorner);
	terminal_put(x+_w, y, _trcorner);
	terminal_put(x, y+_h, _blcorner);
	terminal_put(x+_w, y+_h, _brcorner);
	//center fill
	for (int i = 1; i < _w; i++) {
		for (int j = 1; j < _h; j++) {
			terminal_put(x + i, y + j, CHAR_EMPTY);
		}
	}
	//string prints
	terminal_print_ext(x + 1, y + 1, _w - 1, _h - 1, TK_ALIGN_LEFT, _message.c_str());
	terminal_print_ext(x, y + _h, _w+1, 1, TK_ALIGN_CENTER, _title.c_str());

}