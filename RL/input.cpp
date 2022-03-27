#include "input.h"

Input::Input() {
	return;
}

bool Input::doEventInput() {
	resetInput();
	while (terminal_has_input()) {
		int key = terminal_read();
		//printf("registered %d\n", key);

		if (key == TK_MOUSE_MOVE) {
			_mouseX = terminal_state(TK_MOUSE_X);
			_mouseY = terminal_state(TK_MOUSE_Y);
			//printf("%d %d\n", _mouseX, _mouseY);
		}
		else if (key < TK_KEY_RELEASED) {
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

bool Input::isKeyPressed(const int key) {
	return _pressedKeys.count(key);
}

bool Input::isKeyHeld(const int key) {
	return _heldKeys.count(key) && _heldKeys.at(key);
}

bool Input::isKeyReleased(const int key) {
	return _releasedKeys.count(key);
}

void Input::getMousePos(int* x, int* y) {
	*x = _mouseX;
	*y = _mouseY;
}