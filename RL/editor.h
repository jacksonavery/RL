#pragma once
#include <vector>
#include <BearLibTerminal.h>
#include <iostream>
#include <fstream>
#include "globals.h"
#include "tile.h"
#include "input.h"
#include "uibox.h"
#include "picker.h"
#include "fileDialog.h"

/*
 * ==Editor Class==
 * move with MMB & drag
 * f to invert
 * ctrl s to save
 * ctrl shift s to change name and save
 * ctrl a to open
 * 1,2,3 to mask to FGC,BGC,CHAR
 */

enum states {
	direct,
	picker
};

class Editor {
public:
	Editor(Input* input, int w, int h, const wchar_t* title = L"untitled.chs");
	~Editor();
	void update(int elapsedTime);
	void draw();

	//returns whether given coords are within canvas bounds
	static bool areValidCoords(int x, int y, int w, int h);
private:
	//load file
	void loadFile();
	//save file
	void saveFile(bool newName = false);
	//calls terminal_put with a tile
	void drawSingleTile(int x, int y, Tile* tile);
	//stores a tile into the vector.
	//return 0 if out of bounds.
	bool storeSingleTile(int x, int y, Tile* tile, int mask = 0xFFFF);
	//get a tile at a coordinate
	Tile getTile(int x, int y);
	//either work directly on the screen or redirect input management to
	//an opened ui
	void doDirectInput();
	void doPicker();
	//void doStrEntry();
	//move camera with the mouse
	void doMMBMove();
	//draw call for diff UI states
	void drawDirect();
	void drawPicker();
	void drawCursor();
	
	//the current canvas
	std::vector<Tile> _tiles;
	//name of current canvas
	std::wstring _canvasTitle;
	//so we can get key status remotely
	Input* _input;
	//size of current canvas
	int _w, _h;
	//external box
	UIBox _outline;
	//state: UI window or not
	int _state;
	//the "brush"
	Tile _brushTile;
	//color/char picker window
	Picker* _picker;
	//camera coords
	int _cx, _cy;
	//mouse coords
	int _mx, _my;
	//old mouse coords for MMB movement, and camera equiv
	int _fmx, _fmy;
	int _fcx, _fcy;
	//picker coords
	int _px, _py;
};