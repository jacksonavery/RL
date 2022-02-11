#include "tileHandler.h"

#include <iostream>
#include "window.h"
#include "textbox.h"

TileHandler::TileHandler(const std::string fontPath, int fontSize) {
	_font = loadFont(fontPath, fontSize);

	TextBox* tb = new TextBox(u"message in the box tho? he do be displaying characters", 10, 10, 16, 8);
	_popups.push_back(tb);
}

TileHandler::~TileHandler() {
	//yeah
}

void TileHandler::draw() {
	drawTileSet(_bgTiles);
	for (int i = 0; i < _popups.size(); i++) {
		auto t = _popups.at(i);
		drawTileSet(t->data, t->x, t->y, t->w, t->h);
	}
}

void TileHandler::drawTileSet(Tile* tileset, int x, int y, int w, int h) {
	SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
	for (int j = h-1; j >= 0; j--) {
		for (int i = 0; i < w; i++) {
			auto spriteptr = getSprite(tileset[i + j * w].character);
			Tile* a = &tileset[i + j * w];
			//bg
							//transforms
			_textRect.x = (x + (i % w)) * globals::tileSize;
			_textRect.y = (y + j) * globals::tileSize;
			_textRect.w = globals::tileSize;
			_textRect.h = globals::tileSize;
			SDL_SetRenderDrawColor(Window::renderer, a->bgcolor.r, a->bgcolor.g, a->bgcolor.b, a->bgcolor.a);
			SDL_RenderFillRect(Window::renderer, &_textRect);
			//fg
			SDL_QueryTexture(spriteptr, 0, 0, &_textRect.w, &_textRect.h);
			//adjust x/y pos of chars?
			SDL_SetTextureColorMod(spriteptr, a->fgcolor.r, a->fgcolor.g, a->fgcolor.b);
			SDL_RenderCopy(Window::renderer, spriteptr, 0, &_textRect);
		}
	}
}

TTF_Font* TileHandler::loadFont(const std::string fontPath, int fontSize) {
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font)
		printf("Failed to load font '%s':%s\n", fontPath, SDL_GetError());
	return font;
}

SDL_Texture* TileHandler::loadTextTexture(Uint16 character) {
	auto textSurface = TTF_RenderUNICODE_Blended(_font, &character, SDL_Color{255, 255, 255, 255});
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

void TileHandler::makeStringNaive(const char16_t* string, Tile* destTileSet, int x, int y, int w, int h, int textw, int texth) {
	//i is the index of the string, posi is the index in physical space
	int i = 0;
	int posi = 0;

	while (string[i] != u'\0' && posi < w*h) {
		//Tile* currtile = &destTileSet[(posi % w + x) + (posi / w + y) * w];
		Tile* currtile = &destTileSet[(posi%w + x) + (posi / w + y)*textw];
		currtile->character = string[i];
		posi++;
		i++;
	}
}