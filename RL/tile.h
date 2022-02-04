#pragma once
#include <SDL_ttf.h>

class Tile {
public:
	Tile(int x, int y, int w, int h, int r, int g, int b, int a);

	void draw() const;
private:
	int _x, _y, _w, _h, _r, _g, _b, _a;
	Uint16 _char[2];
};