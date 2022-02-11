#pragma once
#include "popup.h"
#include "globals.h"

struct TextBox : public Popup {
	TextBox(const char16_t* string, int x = 0, int y = 0, int w = globals::tWidth, int h = globals::tHeight);
	~TextBox();
};