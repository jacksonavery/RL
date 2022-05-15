#include "window.h"

Window::Window(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height) {
	if (!init())
		terminal_close();

	gameLoop();
}

Window::~Window() {
	delete _handler;
	delete _logger;
	delete _input;
}

bool Window::init() {
	//open terminal
	if (!terminal_open())
		return false;
	//set window settings
	if (!terminal_setf("window: size = %dx%d", globals::tWidth, globals::tHeight))
		return false;

	_input = new Input();
	_logger = new Logger();
	_handler = _tileEditor = new TileEditor(_input, _logger, 32, 32);

	return true;
}

void Window::gameLoop() {

	//rudimentary fps tracker
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsedTime;

	while (!_closed) {
		elapsedTime = end - start;
		start = std::chrono::steady_clock::now();
		
		_closed = update(elapsedTime.count());
		draw();
		_input->doEventInput();

		end = std::chrono::steady_clock::now();
	}

	terminal_close();
}

bool Window::update(int elapsedTime) {
	int flags = _handler->updateHandler(elapsedTime);
	
	switch (flags)
	{
	case handlerReturns::nothing:
	default:
		break;
	case handlerReturns::close:
		return true;
		break;
	case handlerReturns::tileeditor:
		_handler = _tileEditor;
		break;
	case handlerReturns::overeditor:
		_handler = _overEditor;
		break;
	case handlerReturns::game:
		//no game atm
		break;
	}
	return false;
}

void Window::draw() {
	terminal_bkcolor(colors::black);
	terminal_clear();
	_handler->drawHandler();
	terminal_refresh();
}