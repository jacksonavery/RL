#pragma once
#include <BearLibTerminal.h>
#include <string>
#include <vector>
#include <algorithm>
#include "colors.h"
#include "globals.h"

class Logger {
public:
	Logger();
	~Logger();

	void logMessage(std::wstring message, int timeout = 120);
	void update();
	void draw();
private:
	std::vector<std::wstring> _messages;
	int _timer;
	const int maxmsgs = 5;
};