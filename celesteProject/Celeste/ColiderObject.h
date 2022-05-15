#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/TextureHolder.h"

using namespace sf;

class ColiderObject
{
private:


public:
	ColiderObject();
	virtual void Init();
	virtual void Update(float dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);


};
