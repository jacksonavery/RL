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

	void logMessage(std::wstring message, int timeout = 180);
	void update();
	void draw();
private:
	std::vector<std::wstring> _messages;
	int _timer;
	int maxmsgs = 1;
};