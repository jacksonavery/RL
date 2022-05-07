#include "coordHelper.h"

bool coordHelper::areValidCoords(int x, int y, int w, int h) {
	if (x < 0 || y < 0 || x > w - 1 || y > h - 1) {
		return false;
	}
	return true;
}

std::vector<Tile*> coordHelper::getSubset(int x, int y, int w, int h, std::vector<Tile>* tiles, int tw, int th) {
	if (!areValidCoords(x, y, tw, th))
		return std::vector<Tile*>();
	if (!areValidCoords(x+w, y+h, tw, th))
		return std::vector<Tile*>();
	
	std::vector<Tile*> ret;
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			ret.push_back(&tiles->at(x + i + (y + j) * w));
		}
	}
	return ret;
}