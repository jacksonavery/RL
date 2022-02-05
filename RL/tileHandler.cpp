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
			_textRect.x = i * globals::tileSize;
			_textRect.y = j * globals::tileSize;
			SDL_QueryTexture(spriteptr, 0, 0, &_textRect.w, &_textRect.h);
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