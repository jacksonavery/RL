#pragma once
#include <BearLibTerminal.h>
#include <string>
#include <iostream>
#include <chrono>
#include "input.h"
#include "editor.h"
//#include "uibox.h"

class Window {
public:
	Window(const std::string& Title, int width, int height);
	~Window();
private:
	bool init();

	void gameLoop();
	//returns 1 if closed
	int update(int elapsedTime);
	void draw();

	std::string _title = "window";
	int _width = 800;
	int _height = 600;

	bool _closed = false;
	Input* _input = nullptr;
	Editor* _handler = nullptr;

	int _ET = 0;
};