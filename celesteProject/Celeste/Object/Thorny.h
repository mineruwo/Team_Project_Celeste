#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "../Utils/TextureHolder.h"
#include "ColiderObject.h"
#include <iostream>

using namespace sf;

class Thorny : public ColiderObject
{
private:
	Player player;
	String thornyTexture;
	Sprite thornyObj;
	RectangleShape thornyBox;
	Vector2f thronyPos;


public:
	Thorny();
	void Init();
	void Update(Player &player);
	void Draw(RenderWindow& window);
};

