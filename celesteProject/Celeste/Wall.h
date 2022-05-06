#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Wall
{
private:
	FloatRect wallRect;

public:
	Wall(int top, int left, int width, int height);
	Wall(FloatRect setwall);
	const FloatRect GetWallRect();
};