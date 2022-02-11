#include <SDL_ttf.h>
#include "globals.h"
#include "window.h"


SDL_Renderer *Window::renderer = nullptr;

Window::Window(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height) {
	if (!init()) 
		_closed = true;

	gameLoop();
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(_window);
	//IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to init SDL:%s\n", SDL_GetError());
		return false;
	}

	//if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
	//	printf("Failed to init SDL_IMAGE:%s\n", SDL_GetError());
	//	return false;
	//}

	if (TTF_Init() == -1) {
		printf("Failed to init SDL_ttf:%s\n", SDL_GetError());
		return false;
	}

	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0);
	if (!_window) {
		printf("Failed to create window:%s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Failed to create renderer:%s\n", SDL_GetError());
		return false;
	}

	return true;
}

void Window::gameLoop() {
	_th = new TileHandler(globals::font, globals::tileSize);

	while (!_closed) {
		doEventInput();
		draw();
	}

	delete _th;
}

void Window::doEventInput() {
	resetInput();

	SDL_Event ev;
	if (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT:
			_closed = true;
			break;
		case SDL_KEYDOWN:
			handleKeyPress(ev);
			break;
		case SDL_KEYUP:
			handleKeyRelease(ev);
			break;
		default:
			break;
		}
	}
	if (_pressedKeys[SDL_SCANCODE_ESCAPE])
		_closed = true;
}

void Window::resetInput() {
	_pressedKeys.clear();
}

void Window::handleKeyPress(const SDL_Event& ev) {
	_pressedKeys[ev.key.keysym.scancode] = true;
	_heldKeys[ev.key.keysym.scancode] = true;
}

void Window::handleKeyRelease(const SDL_Event& ev) {
	_releasedKeys[ev.key.keysym.scancode] = true;
	_heldKeys[ev.key.keysym.scancode] = false;
}

void Window::draw() {
	SDL_RenderClear(renderer);
	_th->draw();
	SDL_RenderPresent(renderer);
}