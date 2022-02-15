#include "window.h"

#include <algorithm>
#include <SDL_ttf.h>
#include "globals.h"

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
	if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER) != 0) {
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
	_input = new Input();
	_th = new TileHandler(globals::font, globals::tileSize, _input);

	int LAST_UPDATE_TIME = SDL_GetTicks();

	while (!_closed) {
		_closed = _input->doEventInput();

		//framerate min
		const int CURR_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURR_TIME_MS - LAST_UPDATE_TIME;
		update(std::min(ELAPSED_TIME_MS, globals::MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURR_TIME_MS;

		draw();
	}

	delete _th;
	delete _input;
}

void Window::draw() {
	SDL_RenderClear(renderer);
	_th->drawRT();
	SDL_RenderPresent(renderer);
}

void Window::update(int elapsedTime) {
	_th->update(elapsedTime);
}