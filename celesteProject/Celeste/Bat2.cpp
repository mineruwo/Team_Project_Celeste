#include "Bat2.h"
#include "Utils/Utils.h"
#include "Utils/InputMgr.h"

Bat2::Bat2()
{
    shape.setPosition(0, 0);
    shape.setSize(Vector2f(100, 1920));
    shape.setFillColor(Color::White);
    position = Vector2f(0, 0);

    batRect = shape.getGlobalBounds();
}

FloatRect Bat2::GetGlobalBounds()
{
    return shape.getGlobalBounds();
}

FloatRect Bat2::GetBatRect()
{
    return batRect;
}

const RectangleShape &Bat2::GetShape()
{
    return shape;
}

void Bat2::Update(std::vector <Wall *> walls)
{

}

void Bat2::SetPosition(Vector2f pos)
{
    position = pos;
}
