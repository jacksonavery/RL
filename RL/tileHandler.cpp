#include "tileHandler.h"
#include <iostream>
#include "window.h"

TileHandler::TileHandler(const std::string fontPath, int fontSize) {
	_font = loadFont(fontPath, fontSize);
}

void TileHandler::draw() {
	//_textRect.w = globals::tileSize;
	//_textRect.h = globals::tileSize;
	for (int i = 0; i < globals::tWidth; i++) {
		for (int j = 0; j < globals::tHeight; j++) {
			auto spriteptr = getSprite(_tiles[i][j].character);
			SDL_QueryTexture(spriteptr, 0, 0, &_textRect.w, &_textRect.h);
			_textRect.x = i * globals::tileSize; //(i-1) ~~ + (globals::tWidth - _textRect.w) / 2 ;
			_textRect.y = j * globals::tileSize;
			SDL_SetTextureColorMod(spriteptr, _tiles[i][j].fgcolor.r, _tiles[i][j].fgcolor.g, _tiles[i][j].fgcolor.b);
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
		printf("Failed to load create text surface:%s\n", SDL_GetError());

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Window::renderer, textSurface);
	if (!textTexture)
		printf("Failed to load create texture from text surface:%s\n", SDL_GetError());

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

void TileHandler::drawString(const char16_t* string, int x, int y, int w, int h, bool smartWordCut) {
	//i is the index of the string, posi is the index in physical space
	int i = 0;
	int posi = 0;
	//make everything fit
	if (w == 0 || x + w > globals::tWidth)
		w = globals::tWidth - x;
	if (h == 0 || y + h > globals::tHeight)
		h = globals::tHeight - y;

	while (string[i] != u'\0' && posi < w*h) {
		Tile* currtile = &_tiles[posi % w + x][posi / w + y];
		//add dash if across a border
		//(whole segment skipped if smart cut is off)
		if (smartWordCut && posi % w == w - 1 && string[i] != u' ' && string[i+1] != u' ') {
			//just skip to next line if first letter of word
			if (string[i-1] == u' ') {
				currtile->character = u' ';
				posi++;
				continue;
			}
			currtile->character = u'-'; //0x2014;
			posi++;
			continue;
		}
		//don't start a line with a space
		if (posi % w == 0 && string[i] == u' ') {
			i++;
			continue;
		}
		//respect '\n's
		if (string[i] == u'\n') {
			posi = (posi / w) * w + w;
			i++;
			continue;
		}
		currtile->character = string[i];
		posi++;
		i++;
	}
}