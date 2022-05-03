#include "logger.h"

Logger::Logger() {

}

Logger::~Logger() {

}

void Logger::logMessage(std::wstring message, int timeout) {
	_messages.push_back(message);
	_timer += timeout;

	// call draw immediately so logs happen instantaneously instead of
	// waiting till next draw cycle.
	draw();
	_timer++;
}

void Logger::update() {
	if (_timer > 0)
		_timer--;
}

void Logger::draw() {
	if (_timer > 0) {
		terminal_bkcolor(colors::black);
		terminal_color(colors::white);
		terminal_print(1, globals::tHeight - 3, _messages[_messages.size() - 1].c_str());
		terminal_color(colors::grey);

		int nummsgs = std::min(maxmsgs, (int) _messages.size());
		for (int i = 1; i < nummsgs; i++) {
			terminal_print(1, globals::tHeight - 3 - i, _messages[_messages.size() - 1 - i].c_str());
		}
	}
}