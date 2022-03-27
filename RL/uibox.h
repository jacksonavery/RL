#pragma once

#include "geometric character points.h"
#include <cstdio>
#include <string>
#include <BearLibTerminal.h>

#define UIBOX_OUTLINE_CENTERED 0
#define UIBOX_OUTLINE_OUTER 1

class UIBox {
public:
	UIBox(int x, int y, int w, int h, const wchar_t* message, const wchar_t* title = L"", int outlinestyle = UIBOX_OUTLINE_CENTERED);
	~UIBox();
	void draw();
	/*
	 * expects one of UIBOX_OUTLINE_CENTERED (def), UIBOX_OUTLINE_OUTER
	 */
	void set_outline(int outlinestyle);
private:
	wchar_t _tlcorner;
	wchar_t _trcorner;
	wchar_t _blcorner;
	wchar_t _brcorner;
	wchar_t _upper;
	wchar_t _lower;
	wchar_t _left;
	wchar_t _right;

	int _x;
	int _y;
	int _w;
	int _h;
	std::wstring _message;
	std::wstring _title;
};