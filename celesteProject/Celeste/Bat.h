#pragma once
#include <SFML/Graphics.hpp>
#include "Player/Player.h"

using namespace sf;

class Bat
{
private:
	Vector2f position;
	RectangleShape shape;

	FloatRect batRect;

public:
	Bat(int top, int left, int width, int height);
	Bat(float _x, float _y);

	FloatRect GetGlobalBounds();

	FloatRect GetBatRect();
	const RectangleShape &GetShape();
	void Update();

};