#pragma once
#include <BearLibTerminal.h>
#include <map>

class Input {
public:
	Input();

	bool isKeyPressed(int key);
	bool isKeyHeld(int key);
	bool isKeyReleased(int key);

	bool anyKeyHeld();

	//return false to quit game
	bool doEventInput();
private:
	void resetInput();
	void handleKeyPress(int key);
	void handleKeyRelease(int key);

	std::map<int, bool> _pressedKeys;
	std::map<int, bool> _heldKeys;
	std::map<int, bool> _releasedKeys;
};