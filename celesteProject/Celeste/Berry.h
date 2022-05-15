#pragma once
#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Utils/TextureHolder.h"
#include "ColiderObject.h"
#include <iostream>

using namespace sf;


class Berry : public ColiderObject
{
private:
	Player player;
	String BerryTexture;
	Sprite* BerryObj;
	Vector2f berryPosition;
	float GetBerryDeley;
	bool isGetBerry;
	float Speed;

	float berrySpeed;


public:
	Berry();
	void Init();
	void MoveBerry(float dt, Player &player);
	void ColliderBerry(Player player);
	void GetPlayerPosition(Vector2f Position);
	void Update(Player player, float dt);
	void Draw(RenderWindow& window);

};

