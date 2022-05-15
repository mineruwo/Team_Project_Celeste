#include "PlayerHair.h"

PlayerHair::PlayerHair()
{
	convex.setPointCount(9);
	convex.setPoint(1, Vector2f(4.f, 0.f));
	convex.setPoint(2, Vector2f(9.f, 0.f));
	convex.setPoint(3, Vector2f(10.f, 1.f));
	convex.setPoint(4, Vector2f(11.f, 3.f));
	convex.setPoint(5, Vector2f(11.f, 6.f));
	convex.setPoint(6, Vector2f(9.f, 8.f));
	convex.setPoint(7, Vector2f(0.f, 4.f));
	convex.setPoint(8, Vector2f(2.f, 3.f));
	convex.setPoint(9, Vector2f(1.f, 2.f));
}
