#include "Bat.h"
#include "Utils/Utils.h"
#include "Utils/InputMgr.h"

Bat::Bat()
{
    shape.setPosition(0, 720 * 0.5f);
    shape.setSize(Vector2f(1920, 100));
    shape.setFillColor(Color::White);


	position = Vector2f( 0, 720 * 0.5f);


	batRect = shape.getGlobalBounds();
}

FloatRect Bat::GetGlobalBounds()
{
    return shape.getGlobalBounds();
}

FloatRect Bat::GetBatRect()
{
    return batRect;
}

//Sprite Bat::GetSprite()
//{
//	return sprite;
//}

const RectangleShape &Bat::GetShape()
{
    return shape;
}


void Bat::Update(std::vector <Wall*> walls)
{
   
}

void Bat::SetPosition(Vector2f pos)
{
	position = pos;
}
