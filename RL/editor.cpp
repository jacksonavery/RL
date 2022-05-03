#include "editor.h"

//masks for what to paint
#define MASK_FGCOLOR 1
#define MASK_BGCOLOR 2
#define MASK_CHARACT 4

Editor::Editor(Input* input, int w, int h, const wchar_t* title) : _input(input), _w(w), _h(h) {
	//def draw character
	_brushTile = Tile(L'ı', 1, 0);
	//disable pencil
	_doingPencil = false;
	//picker
	_picker = new Picker(&_brushTile, _input);
	//null cmdhndler
	_commandHandler = nullptr;
	//new logger
	_logger = new Logger;
	//no windows open by def
	_state = states::direct;
	//not closed
	_closed = false;

	//init file
	newFile(w, h);
}

Editor::~Editor() {
	delete(_picker);
	delete(_commandHandler);
	delete(_logger);
}

int Editor::update(int elapsedTime) {
	//only allows current 'state' to get input.
	switch (_state) {
	case states::direct:
		doDirectInput();
		break;
	case states::picker:
		doPicker();
		break;
	default:
		printf("Editor: Unrecognized state %d", _state);
		_state = states::direct;
		break;
	}
	//logger is transcendential
	_logger->update();
	//ckeck for closing regardless of state
	if (_input->isKeyPressed(TK_CLOSE) || _input->isKeyPressed(TK_Q) && _input->isKeyHeld(TK_CONTROL)) {
		promptSave();
		_closed = true;
	}

	return _closed;
}

void Editor::loadFile() {
	std::wstring filePath = FileDialog::loadFile(L"Character Set File (*.chs)\0*.chs\0");
	if (filePath.empty())
		return;

	std::ifstream file;
	file.open(filePath);
	if (!file.is_open()) {
		wprintf(L"could not open file %ls\n", filePath);
		return;
	}

	//actual read
	file.read((char*)&_w, sizeof(_w));
	file.read((char*)&_h, sizeof(_h));
	
	//just call newfile
	newFile(_w, _h);

	for (int i = 0; i < _w*_h; i++) {
		file.read((char*)&_tiles[i].character, sizeof(int));
		file.read((char*)&_tiles[i].bgcolor, sizeof(int));
		file.read((char*)&_tiles[i].fgcolor, sizeof(int));
	}

	file.close();

	//assign internal path
	_canvasPath = filePath;

	//canvas modifications
	_canvasTitle = filePath.substr(filePath.rfind(L"\\") + 1);
	_outline.setTitle(_canvasTitle.c_str());
	_outline = UIBox(_w + 2, _h + 2, L"", _canvasTitle.c_str());

	//log
	std::wstring logmsg = L"Opened file `";
	logmsg.append(_canvasTitle);
	logmsg.append(L"`");
	_logger->logMessage(logmsg);
}

void Editor::saveFile() {
	//if need a new name, prompt for it.
	//otherwise save with existing name
	std::wstring filePath;
	if (!_canvasPath.compare(L"") || _input->isKeyHeld(TK_SHIFT)) {
		filePath = FileDialog::saveFile(L"Character Set File (*.chs)\0*.chs\0");
		if (filePath.empty())
			return;
	}
	else {
		filePath = _canvasPath;
	}

	std::ofstream file;
	file.open(filePath);
	if (!file.is_open()) {
		wprintf(L"could not save file %ls\n", filePath);
		return;
	}

	//actual write
	file.write((char*)&_w, sizeof(_w));
	file.write((char*)&_h, sizeof(_h));
	_tiles.resize(_w*_h);
	for (int i = 0; i < _w*_h; i++) {
		file.write((char*)&_tiles[i].character, sizeof(int));
		file.write((char*)&_tiles[i].bgcolor, sizeof(int));
		file.write((char*)&_tiles[i].fgcolor, sizeof(int));
	}

	file.close();

	//assign internal path
	_canvasPath = filePath;

	//canvas mods
	_canvasTitle = filePath.substr(filePath.rfind(L"\\") + 1);
	_outline.setTitle(_canvasTitle.c_str());

	//update commandHandler
	_commandHandler->callOnSave();

	//log
	std::wstring logmsg = L"Saved file `";
	logmsg.append(_canvasTitle);
	logmsg.append(L"`");
	_logger->logMessage(logmsg);
}

void Editor::newFile(int w, int h, bool fill) {
	//reassign internal vals
	_w = w;
	_h = h;
	//center camera
	_cx = -globals::tWidth / 2 + _w / 2;
	_cy = -globals::tHeight / 2 + _h / 2;
	//update uibox
	_canvasTitle.assign(L"untitled");
	_outline = UIBox(_w + 2, _h + 2, L"", _canvasTitle.c_str());
	//resize canvas itself
	_tiles.clear();
	if (fill)
		_tiles.resize(_w*_h, _brushTile);
	else
		_tiles.resize(_w*_h);
	//reset filepathing so we prompt 'save as' functionality
	_canvasPath = L"";
	//reset commandHandler. this is inelegant
	if (_commandHandler)
		delete(_commandHandler);
	_commandHandler = new CommandHandler();
}

void Editor::doDirectInput() {
	//enter picker mode
	if (_input->isKeyPressed(TK_SPACE)) {
		_state = states::picker;
		_px = _mx;
		_py = _my;
		return;
	}

	//save
	if (_input->isKeyPressed(TK_S) && _input->isKeyHeld(TK_CONTROL)) {
		saveFile();

	}
	//load
	if (_input->isKeyPressed(TK_A) && _input->isKeyHeld(TK_CONTROL)) {
		promptSave();
		loadFile();
	}

	//create new
	if (_input->isKeyPressed(TK_N) && _input->isKeyHeld(TK_CONTROL)) {
		promptSave();

		std::wstring temp;
		int tempw = 0;
		int temph = 0;
		//width
		temp = doStrEntry(L"new width:");
		if (temp.compare(L"") == 0)
			return;
		try { tempw = std::stoi(temp); }
			catch (std::invalid_argument iae) { return; }
		
		//height
		temp = doStrEntry(L"new height (or `s`quare):");
		if (temp.compare(L"") == 0)
			return;
		if (temp.compare(L"s") == 0)
			temph = tempw;
		else try { temph = std::stoi(temp); }
			catch (std::invalid_argument iae) { return; }

		_w = tempw;
		_h = temph;
		newFile(_w,_h);
	}


	//undo and redo
	if (_input->isKeyPressed(TK_Z) && _input->isKeyHeld(TK_CONTROL)) {
		if (_input->isKeyHeld(TK_SHIFT)) {
			_commandHandler->redoCommand();
		}
		else {
			_commandHandler->undoCommand();
		}
	}


	//movement.
	if (_input->isKeyHeld(TK_MOUSE_MIDDLE)) {
		doMMBMove();
	}

	//invert currtile
	if (_input->isKeyPressed(TK_F)) {
		auto a = _brushTile.bgcolor;
		_brushTile.bgcolor = _brushTile.fgcolor;
		_brushTile.fgcolor = a;
	}

	//TODO: rotate currtile
	if (_input->isKeyPressed(TK_R)) {
		
	}

	// == mouse pencil. TODO: refactor to updatePencil and so on (prob updateTool(), which will get _currtool) ==
	doPencil();
}

void Editor::promptSave() {
	if (_commandHandler->areChanges()) {
		std::wstring msg = doStrEntry(L"save changes? (*/q):");
		if (msg.compare(L"q") != 0)
			saveFile();
	}
	return;
}

void Editor::doPencil() {
	//handle starting and stopping input
	if (_input->isKeyPressed(TK_MOUSE_LEFT)) {
		_doingPencil = true;
	}
	if (_input->isKeyReleased(TK_MOUSE_LEFT)) {
		_doingPencil = false;
	}

	// this mask code is a little illegible but itll do.
	// if 1,2, or 3 are pressed, it masks to the FG,BG, and CHAR, respectively,
	// muting the unpressed other keys.  supports any combination.
	int mask = 0x0000;
	bool useMask = false;
	if (_input->isKeyHeld(TK_1)) {
		mask |= MASK_FGCOLOR;
		useMask = true;
	}
	if (_input->isKeyHeld(TK_2)) {
		mask |= MASK_BGCOLOR;
		useMask = true;
	}
	if (_input->isKeyHeld(TK_3)) {
		mask |= MASK_CHARACT;
		useMask = true;
	}
	if (!useMask)
		mask = 0xFFFF;

	//modifications
	_input->getMousePos(&_mx, &_my);

	if (_doingPencil) {
		storeSingleTile(_mx + _cx, _my + _cy, &_brushTile, mask);
	}

	if (_input->isKeyHeld(TK_MOUSE_RIGHT)) {
		_brushTile = getTile(_mx + _cx, _my + _cy);
	}
}

void Editor::doPicker() {
	//leave picker mode
	if (_input->isKeyPressed(TK_SPACE)) {
		_state = states::direct;
		// prevent pencil form getting locked on
		_doingPencil = false;
		return;
	}
	//give relative mouse coords to the picker
	_picker->update(_mx - _px, _my - _py);
}

std::wstring Editor::doStrEntry(std::wstring msg) {
	wchar_t a[64] = {};
	terminal_bkcolor(colors::black);
	terminal_color(colors::white);
	terminal_clear_area(1, globals::tHeight - 2, globals::tWidth - 2, 1);
	terminal_print(1, globals::tHeight - 2, msg.c_str());
	int b = terminal_read_str(1 + msg.length(), globals::tHeight - 2, a, sizeof(a) - 1);
	return std::wstring(a);
}

void Editor::draw() {
	//draw bg
	drawDirect();
	//draw any windows
	switch (_state) {
	case states::picker:
		drawPicker();
		break;
	}
	//draw cursor
	//drawCursor();
	// draw logger
	_logger->draw();
}

void Editor::drawDirect() {
	//the outline UIBox
	_outline.draw(-_cx - 1, -_cy - 1);

	//the drawable area
	for (int j = 0; j < _h; j++) {
		for (int i = 0; i < _w; i++) {
			drawSingleTile(i - _cx, j - _cy, &_tiles[i + j * _w]);
		}
	}
	//the preview char on cursor
	_input->getMousePos(&_mx, &_my);
	if (areValidCoords(_mx + _cx, _my + _cy, _w, _h)) {
		terminal_layer(0);
		terminal_color(colors::indexed[_brushTile.fgcolor]);
		terminal_bkcolor(colors::indexed[_brushTile.bgcolor]);
		terminal_put(_mx, _my, _brushTile.character);
	}
}

void Editor::drawPicker() {
	_picker->draw(_px, _py);
}

void Editor::drawCursor() {
	// cursor drawing code. TODO: abstracting for arbitrary cursor styles
	//terminal_layer(1);
	terminal_color(colors::white);
	terminal_bkcolor(colors::black);
	terminal_put(_mx + 1, _my, L']');
	terminal_put(_mx - 1, _my, L'[');
	//terminal_layer(0);
}

void Editor::drawSingleTile(int x, int y, Tile* tile) {   
	terminal_bkcolor(colors::indexed[tile->bgcolor]);
	terminal_color(colors::indexed[tile->fgcolor]);
	terminal_put(x, y, tile->character);
}

bool Editor::areValidCoords(int x, int y, int w, int h) {
	if (x < 0 || y < 0 || x > w - 1 || y > h - 1) {
		//printf("invalid loc\n");
		return false;
	}
	return true;
}

bool Editor::storeSingleTile(int x, int y, Tile* tile, int mask) {
	if (!areValidCoords(x, y, _w, _h))
		return false;
	// masking for certain values
	Tile* oldtile = &_tiles[x + y * _w];
	Tile currtile = _tiles[x + y * _w];
	if (mask & MASK_FGCOLOR)
		currtile.fgcolor = tile->fgcolor;
	if (mask & MASK_BGCOLOR)
		currtile.bgcolor = tile->bgcolor;
	if (mask & MASK_CHARACT)
		currtile.character = tile->character;

	// dont make updates that don't change anything
	if (*oldtile == currtile)
		return false;

	// command must be updated first or currtile will be wrong
	//printf("old: %d, new: %d\n", oldtile->character, currtile.character);
	_commandHandler->addCommand(new TileChangeCommand(x, y, oldtile, &currtile));

	*oldtile = currtile;

	return true;
}

Tile Editor::getTile(int x, int y) {
	if (!areValidCoords(x, y, _w, _h))
		return Tile();
	return _tiles[x + y * _w];
}

void Editor::doMMBMove() {
	//set past coords on original MMB press
	if (_input->isKeyPressed(TK_MOUSE_MIDDLE)) {
		_fmx = _mx;
		_fmy = _my;
		_fcx = _cx;
		_fcy = _cy;
	}
	//update based on current MMB pos
	_cx = _fcx + _fmx - _mx;
	_cy = _fcy + _fmy - _my;
}