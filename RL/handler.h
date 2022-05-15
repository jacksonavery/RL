#pragma once
#include "logger.h"
#include "input.h"

//either `tileEditor`, `chsEditor`, or `game`
class Handler {
public:
	int updateHandler(int elapsedTime) {
		_logger->update();
		if (update(elapsedTime) == handlerReturns::close)
			return close;
		//this is shnasty but writing it here shares it between all handlers
		if (_input->isKeyPressed(TK_F1))
			return handlerReturns::tileeditor;
		if (_input->isKeyPressed(TK_F2))
			return handlerReturns::overeditor;
		if (_input->isKeyPressed(TK_F3))
			return handlerReturns::game;
		return handlerReturns::nothing;
	}

	void drawHandler() {
		draw();
		_logger->draw();
	}
protected:
	virtual int update(int elapsedTime) = 0;
	virtual void draw() = 0;
	Logger* _logger;
	Input* _input;
};