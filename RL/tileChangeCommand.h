#pragma once
#include "command.h"
#include "tile.h"

class TileChangeCommand : public Command {
public:
	TileChangeCommand(int x, int y, Tile* currtile, Tile* newtile) 
		: _x(x), _y(y), currtile(currtile), _futuretile(*newtile) {}

	virtual void redo() override {
		_pasttile.bgcolor = currtile->bgcolor;
		_pasttile.fgcolor = currtile->fgcolor;
		_pasttile.character = currtile->character;
		//printf("redone\n");
		
		currtile->bgcolor = _futuretile.bgcolor;
		currtile->fgcolor = _futuretile.fgcolor;
		currtile->character = _futuretile.character;
	}
	virtual void undo() override {
		currtile->bgcolor = _pasttile.bgcolor;
		currtile->fgcolor = _pasttile.fgcolor;
		currtile->character = _pasttile.character;
	}

private:
	int _x;
	int _y;
	Tile* currtile;
	Tile _pasttile = Tile(L'%',5,7);
	Tile _futuretile;
};