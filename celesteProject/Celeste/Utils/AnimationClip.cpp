#include "AnimationClip.h"

AnimationFrame::AnimationFrame(Texture &tex, const IntRect &coord, const Vector2f &orig)
	:texture(&tex), texCoord(coord), origin(orig)
{
}
