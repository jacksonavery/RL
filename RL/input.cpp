#include "input.h"

Input::Input() {
	return;
}

bool Input::doEventInput() {
	resetInput();
	while (terminal_has_input()) {
		int key = terminal_read();
		//printf("registered %d", key);

		if (key < TK_KEY_RELEASED) {
			//printf("as pressed\n", key);
			handleKeyPress(key);
		}
		else {
			//printf("as released\n", key);
			handleKeyRelease(key - TK_KEY_RELEASED);
		}
		if (key == TK_CLOSE || key == TK_ESCAPE)
			return true;
	}

	return false;
}

void Input::resetInput() {
	_pressedKeys.clear();
}

void Input::handleKeyPress(int key) {
	_pressedKeys[key] = true;
	_heldKeys[key] = true;
}

void Input::handleKeyRelease(int key) {
	_releasedKeys[key] = true;
	_heldKeys[key] = false;
}

bool Input::anyKeyHeld() {
	return (_heldKeys.size() > 0);
}

bool Input::isKeyPressed(int key) {
	return _pressedKeys.count(key);
}

bool Input::isKeyHeld(int key) {
	return _heldKeys.count(key) && _heldKeys.at(key);
}

bool Input::isKeyReleased(int key) {
	return _releasedKeys.count(key);
}