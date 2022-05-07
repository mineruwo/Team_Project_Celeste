#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;

enum class AnimationLoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	Texture texture;
	IntRect texCoord;
	Vector2f origin;
	AnimationFrame(const Texture &tex, const IntRect &coord, const Vector2f &orig);
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType;
	int fps;
};

