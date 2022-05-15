#pragma once
#include <vector>
#include <BearLibTerminal.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "handler.h"
#include "globals.h"
#include "tile.h"
#include "input.h"
#include "uibox.h"
#include "picker.h"
#include "fileDialog.h"
#include "tileChangeCommand.h"
#include "commandHandler.h"
#include "coordHelper.h"

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

class TileEditor : public Handler {
public:
	TileEditor(Input* input, Logger* logger, int w, int h, const wchar_t* title = L"untitled.chs");
	~TileEditor();
	virtual int update(int elapsedTime) override;
	virtual void draw() override;

private:
	//load file
	void loadFile();
	//save file
	void saveFile();
	//create new empty file
	void newFile(int w, int h, bool fill = false);
	//`new` wrapper
	void newFilePrompts();
	//prompt before losing changes. returns whether to go ahead
	//or not
	bool promptSave();
	//calls terminal_put with a tile
	void drawSingleTile(int x, int y, Tile* tile);
	//stores a tile into the vector. return 0 if out of bounds.
	bool storeSingleTile(int x, int y, Tile* tile, int mask = 0xFFFF);
	//get a tile at a coordinate
	Tile getTile(int x, int y);
	//either work directly on the screen or redirect input management to
	//an opened ui
	void doDirectInput();
	void doPicker();
	std::wstring doStrEntry(std::wstring msg = L"");
	//pencil tool
	void doTools();
	//box functions
	void startBox();
	void stopBox();
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
	//full file path of current canvas
	std::wstring _canvasPath;
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
	//command handler
	CommandHandler* _commandHandler;
	//camera coords
	int _cx, _cy;
	//mouse coords
	int _mx, _my;
	//old mouse coords for MMB movement, and camera equiv
	int _fmx, _fmy;
	int _fcx, _fcy;
	//picker coords
	int _px, _py;
	//closed bool
	bool _closed = false;
	//trackers for if a tool is in active use
	bool _doingPencil;
	bool _doingBox;
	//box fill start coords
	int _boxx, _boxy;
};