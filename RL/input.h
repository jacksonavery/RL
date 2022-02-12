#pragma once
#include <SDL.h>
#include <map>

class Input {
public:
	Input();

	bool isKeyPressed(SDL_Scancode key);

	//return false to quit game
	bool doEventInput();
private:
	void resetInput();
	void handleKeyPress(const SDL_Event& ev);
	void handleKeyRelease(const SDL_Event& ev);

	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
};