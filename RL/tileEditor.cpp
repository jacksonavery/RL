#include "tileEditor.h"

//masks for what to paint
#define MASK_FGCOLOR 1
#define MASK_BGCOLOR 2
#define MASK_CHARACT 4

TileEditor::TileEditor(Input* input, Logger* logger, int w, int h, const wchar_t* title) : _w(w), _h(h) {
	//input
	_input = input;
	//logger
	_logger = logger;

	//def draw character
	_brushTile = Tile(CHAR_EMPTY, 1, 0);
	//disable pencil
	_doingPencil = _doingBox = false;
	//picker
	_picker = new Picker(&_brushTile, _input);
	//null cmdhndler
	_commandHandler = nullptr;
	//no windows open by def
	_state = states::direct;
	//not closed
	_closed = false;

	//init file
	newFile(w, h);
}

TileEditor::~TileEditor() {
	delete(_picker);
	delete(_commandHandler);
}

int TileEditor::update(int elapsedTime) {
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
	//ckeck for closing regardless of state
	if (_input->isKeyPressed(TK_CLOSE) || _input->isKeyPressed(TK_Q) && _input->isKeyHeld(TK_CONTROL)) {
		if (promptSave())
			return handlerReturns::close;
	}

	return handlerReturns::nothing;
}

void TileEditor::loadFile() {
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

void TileEditor::saveFile() {
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
		//wprintf(L"could not save file %ls\n", filePath);
		return;
	}

	//actual write
	file.write((char*)&_w, sizeof(_w));
	file.write((char*)&_h, sizeof(_h));
	//_tiles.resize(_w*_h);
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

void TileEditor::newFile(int w, int h, bool fill) {
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

void TileEditor::doDirectInput() {
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
		if(promptSave())
			loadFile();
	}

	//create new
	if (_input->isKeyPressed(TK_N) && _input->isKeyHeld(TK_CONTROL)) {
		if(promptSave())
			newFilePrompts();
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

	//TODO: 'rotate' currtile
	if (_input->isKeyPressed(TK_R)) {
		
	}

	// tools
	doTools();
}

void TileEditor::newFilePrompts() {
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
	newFile(_w, _h);
}

bool TileEditor::promptSave() {
	if (!_commandHandler->areChanges())
		return 1;
	std::wstring msg = doStrEntry(L"There are unsaved changes. Discard? (q/*):");
	if (msg.compare(L"q") == 0)
		return 1;
	return 0;
}

void TileEditor::startBox() {
	_doingBox = true;
	_boxx = _mx + _cx;
	_boxy = _my + _cy;
}

// TODO: does this explode?
#undef min

void TileEditor::stopBox() {
	if (_doingBox) {
		int tlx = std::min(_mx + _cx, _boxx);
		int tly = std::min(_my + _cy, _boxy);
		int w = std::abs(_mx + _cx - _boxx) + 1;
		int h = std::abs(_my + _cy - _boxy) + 1;

		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				storeSingleTile(tlx + i, tly + j, &_brushTile);
			}
		}
	}
	_doingBox = false;
}
	

void TileEditor::doTools() {
	_input->getMousePos(&_mx, &_my);

	//handle starting and stopping input, as well as vars for box tool
	if (_input->isKeyPressed(TK_MOUSE_LEFT)) {
		if (_input->isKeyHeld(TK_CONTROL)) {
			startBox();
		}
		else
			_doingPencil = true;
		_commandHandler->startGroup();
	}
	if (_input->isKeyReleased(TK_MOUSE_LEFT)) {
		stopBox();
		_doingPencil = false;
		_commandHandler->stopGroup();
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
	if (_doingPencil) {
		storeSingleTile(_mx + _cx, _my + _cy, &_brushTile, mask);
	}

	// picker
	if (_input->isKeyHeld(TK_MOUSE_RIGHT)) {
		_brushTile = getTile(_mx + _cx, _my + _cy);
	}
}

void TileEditor::doPicker() {
	//leave picker mode
	if (_input->isKeyPressed(TK_SPACE)) {
		_state = states::direct;
		// prevent pencil form getting locked on
		_doingPencil = false;
		_doingBox = false;
		_commandHandler->stopGroup();
		return;
	}

	// copy-pasted inversion code
	if (_input->isKeyPressed(TK_F)) {
		auto a = _brushTile.bgcolor;
		_brushTile.bgcolor = _brushTile.fgcolor;
		_brushTile.fgcolor = a;
	}

	//give relative mouse coords to the picker
	_picker->update(_mx - _px, _my - _py);
}

std::wstring TileEditor::doStrEntry(std::wstring msg) {
	wchar_t a[64] = {};
	terminal_bkcolor(colors::black);
	terminal_color(colors::white);
	terminal_clear_area(1, globals::tHeight - 2, globals::tWidth - 2, 1);
	terminal_print(1, globals::tHeight - 2, msg.c_str());
	int b = terminal_read_str(1 + msg.length(), globals::tHeight - 2, a, sizeof(a) - 1);
	return std::wstring(a);
}

void TileEditor::draw() {
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
}

void TileEditor::drawDirect() {
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
	if (coordHelper::areValidCoords(_mx + _cx, _my + _cy, _w, _h)) {
		terminal_layer(0);
		terminal_color(colors::indexed[_brushTile.fgcolor]);
		terminal_bkcolor(colors::indexed[_brushTile.bgcolor]);
		terminal_put(_mx, _my, _brushTile.character);
	}
}

void TileEditor::drawPicker() {
	_picker->draw(_px, _py);
}

void TileEditor::drawCursor() {
	// cursor drawing code. TODO: abstracting for arbitrary cursor styles
	//terminal_layer(1);
	terminal_color(colors::white);
	terminal_bkcolor(colors::black);
	terminal_put(_mx + 1, _my, L']');
	terminal_put(_mx - 1, _my, L'[');
	//terminal_layer(0);
}

void TileEditor::drawSingleTile(int x, int y, Tile* tile) {
	terminal_bkcolor(colors::indexed[tile->bgcolor]);
	terminal_color(colors::indexed[tile->fgcolor]);
	terminal_put(x, y, tile->character);
}

bool TileEditor::storeSingleTile(int x, int y, Tile* tile, int mask) {
	if (!coordHelper::areValidCoords(x, y, _w, _h))
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

Tile TileEditor::getTile(int x, int y) {
	if (!coordHelper::areValidCoords(x, y, _w, _h))
		return Tile();
	return _tiles[x + y * _w];
}

void TileEditor::doMMBMove() {
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