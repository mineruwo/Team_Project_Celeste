#include "Snow.h"


Snow::Snow()
{
	resolution.x = VideoMode::getDesktopMode().width + 500;
	resolution.y = VideoMode::getDesktopMode().height;

}

void Snow::initFlake()
{
	sf::CircleShape flake(float(rand()) / (float)(RAND_MAX / 3.0f) + 0.5f);
	flake.setPosition(float(rand() % resolution.x), 0.0f);
	flake.setFillColor(sf::Color::White);

	snowflakes.emplace_back(flake);

	if (numOfSnowflakes == 0)
		numOfSnowflakes = 200;

	if (delay == 0)
		delay = 10;

}

void Snow::Update(Time dt, RenderWindow& window)
{
	elapsed++;

	if (elapsed >= delay && snowflakes.size() < numOfSnowflakes)
	{
		initFlake();
		elapsed = 0;
	}



	offSet = (float)Utils::RandomRange(1, 5) / 10 * -1.f;


	for (unsigned int i = 0; i < snowflakes.size(); i++)
	{
		snowflakes[i].move(snowflakes[i].getRadius() * offSet, snowflakes[i].getRadius() * 0.4f);


		// Don't draw snowflakes that are outside of the window
		if (snowflakes[i].getPosition().y >= resolution.y)
		{
			snowflakes.erase(snowflakes.begin() + i);
		}
	}


}

void Snow::Draw(RenderWindow& window)
{
	for (unsigned int i = 0; i < snowflakes.size(); i++)
	{
		window.draw(snowflakes[i]);
	}

}
