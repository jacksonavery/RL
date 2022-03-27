#include "uibox.h"

UIBox::UIBox(int x, int y, int w, int h, const wchar_t* message, const wchar_t* title, int outlinestyle) :
	_x(x), _y(y), _w(w - 1), _h(h - 1) {
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

void UIBox::draw() {
	//horizontals
	for (int i = 1; i < _w; i++) {
		terminal_put(_x + i, _y, _upper);
		terminal_put(_x + i, _y+_h, _lower);
	}
	//verticals
	for (int i = 1; i < _h; i++) {
		terminal_put(_x, _y + i, _left);
		terminal_put(_x + _w, _y + i, _right);
	}
	//corners
	terminal_put(_x, _y, _tlcorner);
	terminal_put(_x+_w, _y, _trcorner);
	terminal_put(_x, _y+_h, _blcorner);
	terminal_put(_x+_w, _y+_h, _brcorner);
	//center fill
	for (int i = 1; i < _w; i++) {
		for (int j = 1; j < _h; j++) {
			terminal_put(_x + i, _y + j, 0);
		}
	}
	//string prints
	terminal_print_ext(_x + 1, _y + 1, _w - 1, _h - 1, TK_ALIGN_LEFT, _message.c_str());
	terminal_print_ext(_x, _y + _h, _w, 1, TK_ALIGN_CENTER, _title.c_str());

}