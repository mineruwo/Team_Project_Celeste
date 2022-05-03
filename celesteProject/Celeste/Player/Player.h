#pragma once
#include "../Utils/AnimationController.h"
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float GRAVITY = 9.8;



	Sprite sprite;
	Vector2f position;
	AnimationController animation;

	Vector2i resolution;
	IntRect arena;

	Vector2f direction;
	float speed;
	float timer;

	Texture texture;

	std::map<std::string, Texture> texMap;

public:
	Player();

	void Init();

	void Spawn(IntRect arena, Vector2i res);

	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;

	void UpdateInput(Event event);
	void Update(float dt);

	void Draw(RenderWindow &window);

	


};

