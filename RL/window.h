#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include <map>

class Window {
public:
	Window(const std::string& Title, int width, int height);
	~Window();

private:
	bool init();

	void gameLoop();
	void doEventInput();
	void resetInput();
	void handleKeyPress(const SDL_Event& ev);
	void handleKeyRelease(const SDL_Event& ev);
	void draw();

	std::string _title = "window";
	int _width = 800;
	int _height = 600;

	bool _closed = false;

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
};