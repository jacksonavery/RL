#include "input.h"

Input::Input() {
	return;
}

bool Input::doEventInput() {
	resetInput();

	SDL_Event ev;
	if (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT:
			return true;
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
		return true;
	return false;
}

void Input::resetInput() {
	_pressedKeys.clear();
}

void Input::handleKeyPress(const SDL_Event& ev) {
	_pressedKeys[ev.key.keysym.scancode] = true;
	_heldKeys[ev.key.keysym.scancode] = true;
}

void Input::handleKeyRelease(const SDL_Event& ev) {
	_releasedKeys[ev.key.keysym.scancode] = true;
	_heldKeys[ev.key.keysym.scancode] = false;
}

bool Input::anyKeyHeld() {
	return (_heldKeys.size() > 0);
}

bool Input::isKeyPressed(SDL_Scancode key) {
	return _pressedKeys.count(key);
}

bool Input::isKeyHeld(SDL_Scancode key) {
	return _heldKeys.count(key) && _heldKeys.at(key);
}

bool Input::isKeyReleased(SDL_Scancode key) {
	return _releasedKeys.count(key);
}