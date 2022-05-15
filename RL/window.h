#pragma once
#include <BearLibTerminal.h>
#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "globals.h"
#include "colors.h"
#include "geometric character points.h"
#include "input.h"
#include "handler.h"
#include "tileEditor.h"
#include "logger.h"

class Window {
public:
	Window(const std::string& Title, int width, int height);
	~Window();
private:
	bool init();

	void gameLoop();
	//returns true
	bool update(int elapsedTime);
	void draw();

	std::string _title = "window";
	int _width = 800;
	int _height = 600;

	bool _closed = false;
	Input* _input = nullptr;
	Logger* _logger = nullptr;
	Handler* _handler = nullptr;
	Handler* _tileEditor = nullptr;
	Handler* _overEditor = nullptr;
	Handler* _game = nullptr;
};