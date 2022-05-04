#include "Bat.h"

Bat::Bat(int top, int left, int width, int height)
{
    batRect.top = top;
    batRect.left = left;
    batRect.width = width;
    batRect.height = height;
}

Bat::Bat(float _x, float _y)
    :position(_x, _y)
{
    shape.setPosition(position);
    shape.setSize(Vector2f(1920, 100));
    shape.setFillColor(Color::White);
}

FloatRect Bat::GetGlobalBounds()
{
    return shape.getGlobalBounds();
}

FloatRect Bat::GetBatRect()
{
    return batRect;
}

const RectangleShape &Bat::GetShape()
{
    return shape;
}

void Bat::Update()
{
    /*shape.setPosition(position);*/
}