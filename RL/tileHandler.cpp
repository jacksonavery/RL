#include "tileHandler.h"
#include <iostream>
#include "window.h"

TileHandler::TileHandler(const std::string fontPath, int fontSize) {
	_font = loadFont(fontPath, fontSize);

	_textTexture = loadTextTexture((Uint16*)L"‚ ");
	SDL_QueryTexture(_textTexture, 0, 0, &_textRect.w, &_textRect.h);
}

void TileHandler::draw(int x, int y) {
	_textRect.x = x;
	_textRect.y = y;
	SDL_RenderCopy(Window::renderer, _textTexture, 0, &_textRect);

}

TTF_Font* TileHandler::loadFont(const std::string fontPath, int fontSize) {
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font)
		printf("Failed to load font '%s':%s\n", fontPath, SDL_GetError());
	return font;
}

SDL_Texture* TileHandler::loadTextTexture(Uint16* character) {
	auto textSurface = TTF_RenderUNICODE_Solid(_font, character, SDL_Color{255, 255, 255, 255});
	if (!textSurface)
		printf("Failed to load create text surface:%s\n", SDL_GetError());

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Window::renderer, textSurface);
	if (!textTexture)
		printf("Failed to load create texture from text surface:%s\n", SDL_GetError());

	SDL_FreeSurface(textSurface);
	return textTexture;
}