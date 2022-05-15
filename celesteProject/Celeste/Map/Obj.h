#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/TextureHolder.h"

using namespace sf;

class Obj
{
private:
	Sprite setSprite;
	std::string setFilePath;
public:
	Obj();
	Obj(std::string str);
	void Draw(RenderWindow& window);

	void SetFile(std::string file);
	void SetPosition(Vector2f pos);
	std::string GetFilePath();
	Sprite GetSprite();
};

