#pragma once
#include <BearLibTerminal.h>
#include <string>
#include <vector>
#include <algorithm>
#include "colors.h"
#include "globals.h"

#define LOGGER_TIMEOUT 150

class Logger {
public:
	Logger();
	~Logger();

	void logMessage(std::wstring message);
	void update();
	void draw();
private:
	std::vector<std::wstring> _messages;
	int _timer;
	int maxmsgs = 5;
};