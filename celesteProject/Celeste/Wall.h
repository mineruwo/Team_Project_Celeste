#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Wall
{
private:
	int id;
	FloatRect wallRect;
	RectangleShape shape;

public:
	Wall(int top, int left, int width, int height);
	Wall(FloatRect setwall, int id);

	int GetId() { return id;  }
	void DrawWall(RenderWindow& window);
	const FloatRect GetWallRect();
};