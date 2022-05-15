#pragma once
#include <string>
#include <sstream>
#include <iomanip>

enum handlerReturns {
	nothing,
	close,
	tileeditor,
	overeditor,
	game
};

namespace globals {
	const int width = 1920, height = 1080, tileSize = 24;
	//80*45 atm
	const int tWidth = width / tileSize, tHeight = height / tileSize;

	//const int FPS = 60;
	//const int FRAME_TIME = 1000 / FPS;
	//const int MAX_FRAME_TIME = 5 * FRAME_TIME;
	//
	//const int MOVE_DELAY = FRAME_TIME * 3;

	//const std::string font = "fonts/PixelMplus12-Regular.ttf";
	//const std::string font = "fonts/PixelMplus10-Regular.ttf";
	//const std::string font = "fonts/SourceHanSerif-VF.ttf";
}

static std::wstring intToHexString(int conv) {
	std::wostringstream s;
	s << "0x" << std::setiosflags(std::ios::uppercase) << std::setfill(L'0') << std::setw(4) << std::hex << conv;
	return s.str();
}