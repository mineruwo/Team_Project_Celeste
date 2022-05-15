#include "Wall.h"

Wall::Wall(int top, int left, int width, int height)
{
	wallRect.top = top;
	wallRect.left = left;
	wallRect.width = width;
	wallRect.height = height;

	shape.setPosition(wallRect.left, wallRect.top);
	shape.setSize(Vector2f(wallRect.width, wallRect.height));
	shape.setFillColor(Color(0, 0, 0, 0));
}

Wall::Wall(FloatRect setwall)
{
	wallRect = setwall;

	shape.setPosition(wallRect.left, wallRect.top);
	shape.setSize(Vector2f(wallRect.width, wallRect.height));
	shape.setFillColor(Color(0, 0, 0, 0));
}

void Wall::DrawWall(RenderWindow& window)
{
	window.draw(shape);
}

const FloatRect Wall::GetWallRect()
{
	return wallRect;
}

void Wall::TurnOffRect()
{
	shape.setFillColor(Color(0, 0, 0, 0));
}

void Wall::TurnOnRect()
{
	shape.setFillColor(Color(0, 255, 0, 126));
}
