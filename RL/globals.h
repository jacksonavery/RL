#pragma once
#include <string>
namespace globals {
	const int width = 1920, height = 1080, tileSize = 24;
	//80*45 atm
	const int tWidth = width / tileSize, tHeight = height / tileSize;
	const std::string font = "fonts/PixelMplus12-Regular.ttf";
	//const std::string font = "fonts/SourceHanSerif-VF.ttf";
}