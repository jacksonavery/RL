#pragma once
#include <BearLibTerminal.h>
#include <map>

class Input {
public:
	Input();

	bool isKeyPressed(const int key);
	bool isKeyHeld(const int key);
	bool isKeyReleased(const int key);
	void getMousePos(int* x, int* y);

	bool anyKeyHeld();

	void doEventInput();
private:
	void resetInput();
	void handleKeyPress(int key);
	void handleKeyRelease(int key);

	std::map<int, bool> _pressedKeys;
	std::map<int, bool> _heldKeys;
	std::map<int, bool> _releasedKeys;
	int _mouseX, _mouseY;
};