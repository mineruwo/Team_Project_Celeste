#pragma once
#include "SFML/Graphics.hpp"
#include "../Utils/Utils.h"
#include <vector>
#include <random>

using namespace sf;
using namespace std;


class Snow
{
private:
	Vector2i resolution;

	float offSet;

	unsigned int elapsed = 0;
	unsigned int numOfSnowflakes;
	unsigned int delay;
	std::vector<sf::CircleShape> snowflakes;


public:
	Snow();
	void initFlake();
	void Update(Time dt, RenderWindow& window);
	void Draw(RenderWindow& window);


};


