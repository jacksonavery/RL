#include "tileHandler.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <agents.h>
#include "window.h"
#include "textbox.h"
#include "colors.h"

TileHandler::TileHandler(const std::string fontPath, int fontSize, Input* input) {
	_font = loadFont(fontPath, fontSize);
	_input = input;

	//init tileset
	initTileSetTiles(&_bgTiles, 20, 20);
	//_bgTiles.at(2).at(2).character = u'Ç†';

	auto a = new TextBox(u"ãMï˚ÇÃóßèÍÇ¡ÇƒâΩÇæÇÎÇ§", 0, 0, globals::tWidth, globals::tHeight);
	_popups.push_back(a);

	//init voxelset
	//initVoxelSetVoxels(&_voxels, 5, 2);
	//_elevations.push_back(_voxels);
	//initVoxelSetVoxels(&_voxels, 3, 2);
	//_elevations.push_back(_voxels);
	initVoxelSetVoxels(&_voxels, 5, 5);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);


	//init camera
	_camerax = _cameray = 0;
	_camerar = 0;
	_camerah = _elevations.size()-1;
	_timeSinceLastCameraUpdate = 0;

	//init screen
	_screen.resize(globals::tWidth);
	for (int i = 0; i < _screen.size(); i++) {
		_screen.at(i).resize(globals::tHeight, &_transparentTile);
	}
}

TileHandler::~TileHandler() {
	//yeah
}

void TileHandler::update(int elapsedTime) {
	doCameraMovement(elapsedTime);
}

void TileHandler::doCameraMovement(int elapsedTime) {
	_timeSinceLastCameraUpdate += elapsedTime;
	if (_timeSinceLastCameraUpdate > globals::MOVE_DELAY) {
		_camerax += _input->isKeyHeld(SDL_SCANCODE_D) - _input->isKeyHeld(SDL_SCANCODE_A);
		_cameray += _input->isKeyHeld(SDL_SCANCODE_S) - _input->isKeyHeld(SDL_SCANCODE_W);
		_timeSinceLastCameraUpdate = 0;
	}
	//if (_input->isKeyPressed(SDL_SCANCODE_R)) {
	//	_camerar = (_camerar + 1) % 4;
	//}
	if (_input->isKeyPressed(SDL_SCANCODE_Q)) {
		_camerah = std::max(1, _camerah - 1);
	}
	if (_input->isKeyPressed(SDL_SCANCODE_E)) {
		_camerah = std::min((int) _elevations.size() - 1, _camerah + 1);
	}
}

void TileHandler::draw() {
	for (int i = 0; i < _screen.size(); i++) {
		for (int j = 0; j < _screen.at(0).size(); j++) {
			_screen.at(i).at(j) = &_transparentTile;
		}
	}
	
	//drawRTToScreen(&_screen);

	for (int i = 0; i < _popups.size(); i++) {
		drawTileSetToScreen(&_popups.at(i)->data, &_screen);
	}

	drawScreen(&_screen);
}

void TileHandler::drawScreen(std::vector<std::vector<Tile*>>* screen) {
	int h = globals::tHeight;
	int w = globals::tWidth;
	for (int j = h - 1; j >= 0; j--) {
		for (int i = 0; i < w; i++) {
			//printf("i:%d, j:%d\n", i, j);
			Tile* a = screen->at(i).at(j);
			if (a->character == 0)
				continue;
			drawSingleTile(a, i, j);
		}
	}
}


void TileHandler::drawRTToScreen(std::vector<std::vector<Tile*>>* screen) {
	//i and j are screenspace camera coords,
	//xyz are the location of the iterator through space
	int i;
	int j;
	////x/y are initialized here
	int x;
	int y;
	//the y modifier each step, and  bounds
	int ymod = -1;
	int ybound = -1;

	//override for front face
	bool drawSide = false;
	int zHeight = std::min(_elevations.size() - 1, (unsigned int)_camerah);

	//anything we dont need to fidn in the loop
	unsigned int xsize = _elevations.at(0).size();
	unsigned int ysize = _elevations.at(0).at(0).size();

	for (i = _camerax; i < globals::tWidth + _camerax; i++) {
		for (j = _cameray; j < globals::tHeight + _cameray; j++) {
			x = i;
			y = j;
			int z = zHeight;

			//break if outside of drawable set, or forward if along front face
			
			if (x < 0 || x > xsize - 1) {
				continue;
			}
			if (y < 0 || y > ysize - 1) {
				if (y - z <= ysize) {
					y = ysize - 1;
					z -= ysize - y;
					drawSide = true;
				}
				else
					continue;
			}

			// the 'raycast'
			while (true) {
				//check if out of bounds
				if (z < 0) {
					screen->at(i - _camerax).at(j - _cameray) = &_zBoundTile;
					break;
				}
				//the top of the tile
				auto currVox = &_elevations.at(z).at(x).at(y);
				//chech if drawing from front of drawbox
				if (!drawSide) {
					if (currVox->topTile.character != u' ') {
						screen->at(i - _camerax).at(j - _cameray) = &currVox->topTile;
						break;
					}
					//the front face of the tile one further back
					y += ymod;
					if (y == ybound) {
						break;
					}
				}
				drawSide = false;

				currVox = &_elevations.at(z).at(x).at(y);
				if (currVox->sideTile.character != u' ') {
					screen->at(i - _camerax).at(j - _cameray) = &currVox->sideTile;
					break;
				}

				//the tile below
				z--;
			}
		}
	}
}

void TileHandler::drawTileSetToScreen(std::vector<std::vector<Tile>>* tileset, std::vector<std::vector<Tile*>>* screen, int x, int y) {
	//handle right and bottom clip
	int w = tileset->size();
	int h = tileset->at(0).size();
	if (w + x > globals::tWidth)
		w = globals::tWidth - x;
	if (h + y > globals::tHeight)
		h = globals::tHeight - y;

	//handle left and top clip
	int srcxoff = std::max(-x, 0);
	int srcyoff = std::max(-y, 0);

	//i and j iterate through target texture
	for (int j = h - 1; j >= 0; j--) {
		for (int i = srcxoff; i < w; i++) {
			//printf("i:%d, j:%d\n", i, j);
			Tile* a = &tileset->at(i).at(j);
			if (a->character == 0)
				continue;
			screen->at(x + (i % w)).at(y + j) = a;
		}
	}
	//reset clear color at end
	SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
}

void TileHandler::drawSingleTile(Tile* tile, int xpos, int ypos) {
	auto spriteptr = getSprite(tile->character);
	//bg
					//transforms
	_textRect.x = (xpos) * globals::tileSize;
	_textRect.y = (ypos) * globals::tileSize;
	_textRect.w = globals::tileSize;
	_textRect.h = globals::tileSize;
	SDL_SetRenderDrawColor(Window::renderer, tile->bgcolor.r, tile->bgcolor.g, tile->bgcolor.b, tile->bgcolor.a);
	SDL_RenderFillRect(Window::renderer, &_textRect);
	//fg
	SDL_QueryTexture(spriteptr, 0, 0, &_textRect.w, &_textRect.h);
	//i dont like this but it seems to work
		_textRect.y--;
	SDL_SetTextureColorMod(spriteptr, tile->fgcolor.r, tile->fgcolor.g, tile->fgcolor.b);
	SDL_RenderCopy(Window::renderer, spriteptr, 0, &_textRect);
}

TTF_Font* TileHandler::loadFont(const std::string fontPath, int fontSize) {
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font)
		printf("Failed to load font '%s':%s\n", fontPath, SDL_GetError());
	return font;
}

SDL_Texture* TileHandler::loadTextTexture(Uint16 character) {
	auto textSurface = TTF_RenderUNICODE_Blended(_font, &character, cols::white);
	if (!textSurface)
		printf("Failed to create text surface:%s\n", SDL_GetError());

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Window::renderer, textSurface);
	if (!textTexture)
		printf("Failed to create texture from text surface:%s\n", SDL_GetError());

	SDL_FreeSurface(textSurface);

	_spriteSheet[character] = textTexture;
	return textTexture;
}

SDL_Texture* TileHandler::getSprite(Uint16 character) {
	//std::cout << character << std::endl;
	if (_spriteSheet.count(character) == 0) {
		return loadTextTexture(character);
	}
	return _spriteSheet[character];
}

void TileHandler::initTileSetTiles(std::vector<std::vector<Tile>>* destTileSet, int w, int h) {
	Tile a;
	std::vector<Tile> b;
	b.resize(h, a);
	destTileSet->resize(w, b);
}

void TileHandler::initVoxelSetVoxels(std::vector<std::vector<Voxel>>* destTileSet, int w, int h) {
	Voxel a;
	Voxel empt( &Tile(u' '), &Tile(u' ') );
	std::vector<Voxel> b;
	std::vector<Voxel> c;
	b.resize(h, a);
	//b.at(0).topTile.character = u'Å~';
	b.resize(40, empt);
	c.resize(40, empt);
	destTileSet->resize(w, b);
	destTileSet->resize(40, c);
}

void TileHandler::makeStringNaive(const char16_t* string, std::vector<std::vector<Tile>>* destTileSet, int x, int y, int w, int h) {
	//i is the index of the string, posi is the index in physical space
	int i = 0;
	int posi = 0;

	while (string[i] != u'\0' && posi < w*h) {
		Tile* currtile = &destTileSet->at(posi % w + x).at(posi / w + y);
		currtile->character = string[i];
		posi++;
		i++;
	}
}

void TileHandler::makeBoundingBox(std::vector<std::vector<Tile>>* destTileSet, bool isThick) {
	//init to empty tiles
	int w = destTileSet->size();
	if (!w)
		return;
	int h = destTileSet->at(0).size();
	Tile a(u' ', cols::white, cols::black);
	for (int i = 0; i < w*h; i++) {
		destTileSet->at(i%w).at(i/w) = a;
	}
	//top/bot
	for (int i = 0; i < w; i++) {
		destTileSet->at(i).at(0).character = 0x2500 + isThick;
		destTileSet->at(i).at(h-1).character = 0x2500 + isThick;
	}
	//sides
	for (int i = 0; i < h; i++) {
		destTileSet->at(0).at(i).character = 0x2502 + isThick;
		destTileSet->at(w-1).at(i).character = 0x2502 + isThick;
	}
	//corners
	destTileSet->at(0).at(0).character = 0x250C + 3 * isThick;
	destTileSet->at(w-1).at(0).character = 0x2510 + 3 * isThick;
	destTileSet->at(0).at(h-1).character = 0x2514 + 3 * isThick;
	destTileSet->at(w-1).at(h-1).character = 0x2518 + 3 * isThick;
}