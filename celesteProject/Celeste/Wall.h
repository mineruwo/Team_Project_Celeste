#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Wall
{
private:
	FloatRect wallRect;
	RectangleShape shape;

public:
	Wall(int top, int left, int width, int height);
	Wall(FloatRect setwall);

	void DrawWall(RenderWindow& window);
	const FloatRect GetWallRect();

	void TurnOffRect();
	void TurnOnRect();
};