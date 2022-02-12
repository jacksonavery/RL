#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include "input.h"
#include "tileHandler.h"

class Window {
public:
	Window(const std::string& Title, int width, int height);
	~Window();

	static SDL_Renderer* renderer;
private:
	bool init();

	void gameLoop();
	void update(int elapsedTime);
	void draw();

	std::string _title = "window";
	int _width = 800;
	int _height = 600;

	bool _closed = false;

	SDL_Window* _window = nullptr;
	Input* _input = nullptr;

	TileHandler* _th = nullptr;
};