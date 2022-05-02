#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	Vector2f position;

	IntRect arena;

	Vector2f direction;
	float speed;
	float timer;

public:
	Player();

	void Spawn(IntRect arena, Vector2i res);

	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;


};

