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
	_handler = new Editor(_input, 32, 32);

	//rudimentary fps tracker
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsedTime;

	while (!_closed) {
		elapsedTime = end - start;
		start = std::chrono::steady_clock::now();
		
		_closed |= update(elapsedTime.count());
		draw();
		_closed |= _input->doEventInput();

		end = std::chrono::steady_clock::now();
	}

	terminal_close();

	delete _handler;
	delete _input;
}

int Window::update(int elapsedTime) {
	//returned closed flag
	return _handler->update(elapsedTime) & 1;
}

void Window::draw() {
	terminal_bkcolor(colors::black);
	terminal_clear();
	_handler->draw();
	//terminal_print_ext(20, 25, 50, 20, TK_ALIGN_LEFT, L" Siks sencrīz ıgō, th last vizitr frm erth ntrd mai wrld. Nau its yr trn to fīl that pēn. th Gēts r ōpn:\n\n Gēt 1: Dārknis, a wrld v hyūmns.Luk raund yū, thēr evrīwēr.\n Gēt 2: Mai gārds r wācng yū.\n Gēt 3: ōnlī yū [[]].\n Gēt 4: Thērs nō wē aut.\n Gēt 5: Fīl th fair.\n Gēt 6: Pik up yr wepns nd fait, fait, nd dans wth th Devl.");
	terminal_refresh();
}