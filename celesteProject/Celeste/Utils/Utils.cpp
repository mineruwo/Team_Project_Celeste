#include "Utils.h"
#include <iostream>
#include <cmath>

std::random_device Utils::rd;
std::mt19937 Utils::gen(rd());

/*==============================
	텍스트 좌표 preset지정
================================*/
void Utils::SetOrigin(sf::Text &text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}
/*==============================
      도형 좌표 preset지정
================================*/
void Utils::SetOrigin(sf::Shape &shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}
/*==============================
	  그림 좌표 preset지정
================================*/
void Utils::SetOrigin(sf::Sprite &sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}
/*==============================
		  origin 설정
================================*/
void Utils::SetOrigin(sf::Transformable &tr, sf::FloatRect bounds, Pivots preset)
{
	switch (preset)
	{
	case Pivots::LT:
		tr.setOrigin(bounds.left, bounds.top);
		break;
	case Pivots::LC:
		tr.setOrigin(bounds.left, bounds.height * 0.5f);
		break;
	case Pivots::LB:
		tr.setOrigin(bounds.left, bounds.height);
		break;

	case Pivots::CT:
		tr.setOrigin(bounds.width * 0.5f, bounds.top);
		break;
	case Pivots::CC:
		tr.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
		break;
	case Pivots::CB:
		tr.setOrigin(bounds.width * 0.5f, bounds.height);
		break;

	case Pivots::RT:
		tr.setOrigin(bounds.width, bounds.top);
		break;
	case Pivots::RC:
		tr.setOrigin(bounds.width, bounds.height * 0.5f);
		break;
	case Pivots::RB:
		tr.setOrigin(bounds.width, bounds.height);
		break;
	default:
		break;
	}
}
/*==============================
		랜덤 범위 설정
================================*/
int Utils::RandomRange(int min, int excludeMax)
{
	int range = excludeMax - min;
	return min + gen() % range;
}
/*==============================
		    충돌 처리
================================*/
Pivots Utils::CollisionDir(FloatRect standRect, FloatRect testRect)
{
	if (testRect.left < standRect.left + standRect.width
		&& testRect.left + testRect.width > standRect.left + standRect.width)
	{
		return Pivots::LC;
	}
	//오른쪽
	else if (testRect.left + testRect.width > standRect.left && testRect.left < standRect.left)
	{
		return Pivots::RC;
	}

	//위
	else if (testRect.top < standRect.top + standRect.height && testRect.top + testRect.height > standRect.top + standRect.height)
	{
		return Pivots::CT;
	}
	//아래
	else
	{
		return Pivots::CB;
	}

	return Pivots();
}
/*==============================
		  길이를 가지고옴
================================*/
float Utils::GetLength(const Vector2f &vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}
/*==============================
		  정규화 처리
================================*/
Vector2f Utils::Normalize(const Vector2f &vector)
{
	Vector2f v = vector;
	float length = GetLength(vector);

	if (length > 0)
	{
		v /= length;
	}

	return v;
}

float Utils::GetAngel(const Vector2f &from, const Vector2f &to)
{
	Vector2f dir = to - from;
	float radian = atan2(dir.y, dir.x);
	return radian * 180.f / 3.141592;
}
