#pragma once
#include <BearLibTerminal.h>
#include <string>
#include <iostream>
#include "input.h"
#include "editor.h"
//#include "uibox.h"

class BLTWindow {
public:
	BLTWindow(const std::string& Title, int width, int height);
	~BLTWindow();
private:
	bool init();

	void gameLoop();
	void update(int elapsedTime);
	void draw();

	std::string _title = "window";
	int _width = 800;
	int _height = 600;

	bool _closed = false;
	Input* _input = nullptr;
	Editor* _handler = nullptr;

	int _ET = 0;
};