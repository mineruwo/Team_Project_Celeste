#include "Obj.h"

Obj::Obj()
{
}

Obj::Obj(std::string str)
{
	setSprite.setTexture(TextureHolder::GetTexture(str));
	setSprite.setScale(Vector2f(2,2));
	setFilePath = str;
}

void Obj::Draw(RenderWindow& window)
{
	window.draw(setSprite);
}

void Obj::SetFile(std::string file)
{
	setSprite.setTexture(TextureHolder::GetTexture(file));
	setSprite.setScale(Vector2f(2, 2));
	setFilePath = file;
}

void Obj::SetPosition(Vector2f pos)
{
	setSprite.setPosition(pos);
}

std::string Obj::GetFilePath()
{
	return setFilePath;
}

Sprite Obj::GetSprite()
{
	return setSprite;
}

