#include "Bat.h"
#include "Utils/Utils.h"
#include "Utils/InputMgr.h"

//Bat::Bat(int top, int left, int width, int height)
//{
//    batRect.top = top;
//    batRect.left = left;
//    batRect.width = width;
//    batRect.height = height;
//}

//Bat::Bat(float _x, float _y)
//    :position(_x, _y)
//{
//    shape.setPosition(0, 720 * 0.5f);
//    shape.setSize(Vector2f(1920, 100));
//    shape.setFillColor(Color::White);
//}

Bat::Bat()
{
    shape.setPosition(0, 720 * 0.5f);
    shape.setSize(Vector2f(1920, 100));
    shape.setFillColor(Color::White);
}

FloatRect Bat::GetGlobalBounds()
{
    return shape.getGlobalBounds();
}

//FloatRect Bat::GetBatRect()
//{
//    return batRect;
//}

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
	for (auto v : walls)
	{
		if (shape.getGlobalBounds().intersects(v->GetWallRect()))
		{

			Pivots pivot = Utils::CollisionDir(v->GetWallRect(), shape.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				position.x += (v->GetWallRect().left + v->GetWallRect().width) - (shape.getGlobalBounds().left);
				InputMgr::HorInit();
				break;

			case Pivots::RC:
				position.x -= (shape.getGlobalBounds().left + shape.getGlobalBounds().width) - (v->GetWallRect().left);
				InputMgr::HorInit();
				break;

			case Pivots::CT:
				position.y += (v->GetWallRect().top + v->GetWallRect().height) - (shape.getGlobalBounds().top);
				InputMgr::VerInit();
				break;

			case Pivots::CB:
				position.y -= (shape.getGlobalBounds().top + shape.getGlobalBounds().height) - (v->GetWallRect().top);
				InputMgr::VerInit();
				break;

			defalut:
				break;
			}

			shape.setPosition(position);
		}
	}
   
}