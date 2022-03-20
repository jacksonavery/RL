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



/*
 * fades between col1 and col2. mix is [0-255]
 */
//col colmix(const col col1, const col col2, const char mix) {
//	char R = col1.r * (255 - mix) + col2.r * (mix);
//	char G = col1.g * (255 - mix) + col2.g * (mix);
//	char B = col1.b * (255 - mix) + col2.b * (mix);
//	return col{ R,G,B };
//}