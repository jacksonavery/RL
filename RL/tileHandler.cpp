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
	//_bgTiles.at(2).at(2).character = u'��';

	//auto a = new TextBox(u"when the susposter is in", 5, 5);
	//_popups.push_back(a);

	//init voxelset
	initVoxelSetVoxels(&_voxels, 8, 5);

	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);
	_elevations.push_back(_voxels);

	//init camera
	_camerax = _cameray = 0;
	_timeSinceLastCameraUpdate = 0;
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
}

void TileHandler::drawRT() {
	//i and j are screenspace camera coords
	for (int i = _camerax; i < globals::tWidth + _camerax; i++) {
		for (int j = _cameray; j < globals::tHeight + _cameray; j++) {
			//xyz are current voxel's pos
			int x = i;
			int y = j;
			int z = _elevations.size() - 1;

			//break if outside of drawable set
			if (x < 0 || x > _elevations.at(0).size() - 1)
				continue;
			if (y < 0 || y > _elevations.at(0).at(0).size() - 1) {
				continue;
			}

			// the 'raycast'
			while (true) {
				auto currVox = &_elevations.at(z).at(x).at(y);
				if (_elevations.at(z).at(x).at(y).topTile.character != u' ') {
					drawSingleTile(&currVox->topTile, i - _camerax, j - _cameray);
					break;
				}
				
				y--;
				if (y < 0) {
					break;
				}
				currVox = &_elevations.at(z).at(x).at(y);
				if (_elevations.at(z).at(x).at(y).sideTile.character != u' ') {
					drawSingleTile(&currVox->sideTile, i - _camerax, j - _cameray);
					break;
				}

				z--;
				if (z < 0) {
					drawSingleTile(&Tile(u'�E'), i - _camerax, j - _cameray);
					break;
				}
					
			}
		}
	}
}

void TileHandler::drawTileSet(std::vector<std::vector<Tile>>* tileset, int x, int y) {
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
	for (int j = h-1; j >= 0; j--) {
		for (int i = srcxoff; i < w; i++) {
			//printf("i:%d, j:%d\n", i, j);
			Tile* a = &tileset->at(i).at(j);
			if (a->character == 0)
				continue;
			drawSingleTile(a, x + (i % w), y + j);
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

void TileHandler::drawVoxelSet(std::vector<std::vector<Voxel>>* vectorset, int x, int y) {
	//handle right and bottom clip
	int w = vectorset->size();
	if (w == 0)
		return;
	int h = vectorset->at(0).size();
	if (w + x > globals::tWidth)
		w = globals::tWidth - x;
	if (h + y > globals::tHeight)
		h = globals::tHeight - y + 1;

	//handle left and top clip
	int srcxoff = std::max(-x, 0);
	int srcyoff = std::max(-y, 0);

	//		###atm do all wall pass then all floor pass. optimize please##
	for (int j = h - 1; j >= 0; j--) {
		for (int i = srcxoff; i < w; i++) {
			//printf("i:%d, j:%d\n", i, j);
			Tile* a = &vectorset->at(i).at(j).sideTile;
			if (a->character == 0)
				continue;
			drawSingleTile(a, x + (i % w), y + j);

		}
	}
	//i and j iterate through target texture
	for (int j = h - 1; j >= 0; j--) {
		for (int i = srcxoff; i < w; i++) {
			//printf("i:%d, j:%d\n", i, j);
			Tile* a = &vectorset->at(i).at(j).topTile;
			if (a->character == 0)
				continue;
			drawSingleTile(a, x + (i % w), y + j - 1);

		}
	}
	//reset clear color at end
	SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
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
	b.resize(20, empt);
	c.resize(20, empt);
	destTileSet->resize(w, b);
	destTileSet->resize(20, c);
}

//void TileHandler::makeString(const char16_t* string, Tile* destTileSet, int x, int y, int w, int h, bool smartWordCut) {
//	//i is the index of the string, posi is the index in physical space
//	int i = 0;
//	int posi = 0;
//	//make everything fit
//	if (w == 0 || x + w > globals::tWidth)
//		w = globals::tWidth - x;
//	if (h == 0 || y + h > globals::tHeight)
//		h = globals::tHeight - h;
//
//	while (string[i] != u'\0' && posi < w*h) {
//		Tile* currtile = &destTileSet[(posi % w + x) + (posi / w + y) * w];
//		//add dash if across a border
//		//(whole segment skipped if smart cut is off)
//		if (smartWordCut && posi % w == w - 1 && string[i] != u' ' && string[i+1] != u' ') {
//			//just skip to next line if first letter of word
//			if (string[i-1] == u' ') {
//				currtile->character = u' ';
//				posi++;
//				continue;
//			}
//			currtile->character = u'-'; //0x2014;
//			posi++;
//			continue;
//		}
//		//don't start a line with a space
//		if (posi % w == 0 && string[i] == u' ') {
//			i++;
//			continue;
//		}
//		//respect '\n's
//		if (string[i] == u'\n') {
//			posi = (posi / w) * w + w;
//			i++;
//			continue;
//		}
//		currtile->character = string[i];
//		posi++;
//		i++;
//	}
//}

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