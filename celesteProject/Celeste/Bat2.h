#pragma once
#include <SFML/Graphics.hpp>
#include "Player/Player.h"

using namespace sf;

class Bat2
{
private:
	Vector2f position;
	RectangleShape shape;

	FloatRect batRect;

public:
	//Bat(int top, int left, int width, int height);
	//Bat(float _x, float _y);

	Bat2();

	FloatRect GetGlobalBounds();

	FloatRect GetBatRect();

	const RectangleShape &GetShape();

	void Update(std::vector <Wall *> walls);

	void SetPosition(Vector2f pos);
};