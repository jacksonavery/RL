#pragma once
#include <string>
namespace globals {
	const int width = 1920, height = 1080, tileSize = 24;
	//80*45 atm
	const int tWidth = width / tileSize, tHeight = height / tileSize;

	const int FPS = 60;
	const int FRAME_TIME = 1000 / FPS;
	const int MAX_FRAME_TIME = 5 * FRAME_TIME;

	const int MOVE_DELAY = FRAME_TIME * 3;

	//const std::string font = "fonts/PixelMplus12-Regular.ttf";
	//const std::string font = "fonts/PixelMplus10-Regular.ttf";
	const std::string font = "fonts/SourceHanSerif-VF.ttf";
}