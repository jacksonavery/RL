#pragma once
#include "logger.h"

//either `tileEditor`, `chsEditor`, or `game`
class Handler {
public:
	int updateHandler(int elapsedTime) {
		_logger->update();
		return update(elapsedTime);
	}

	void drawHandler() {
		draw();
		_logger->draw();
	}
protected:
	virtual int update(int elapsedTime) = 0;
	virtual void draw() = 0;
	Logger* _logger;
};