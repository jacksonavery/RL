#include "window.h"

#include <algorithm>
#include "globals.h"
#include "colors.h"
#include "geometric character points.h"

Window::Window(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height) {
	if (!init())
		terminal_close();

	gameLoop();
}

Window::~Window() {
	//今しない
}

bool Window::init() {
	//open terminal
	if (!terminal_open())
		return false;
	//set window settings
	if (!terminal_setf("window: size = %dx%d", globals::tWidth, globals::tHeight))
		return false;
	return true;
}

void Window::gameLoop() {
	_input = new Input();
	_handler = new Editor(_input, 32, 32, L"untitled");

	//rudimentary fps tracker
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsedTime;

	while (!_closed) {
		elapsedTime = end - start;
		start = std::chrono::steady_clock::now();
		
		update(elapsedTime.count());
		draw();
		_closed = _closed || _input->doEventInput();

		end = std::chrono::steady_clock::now();
	}

	terminal_close();

	delete _handler;
	delete _input;
}

void Window::update(int elapsedTime) {
	_handler->update(elapsedTime);
}

void Window::draw() {
	_handler->draw();
}