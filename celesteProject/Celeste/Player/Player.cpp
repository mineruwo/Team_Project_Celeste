#include "Player.h"
#include "../Utils/InputMgr.h"
#include <iostream>

Player::Player()
	:speed(START_SPEED)
{	

}

void Player::Init()
{
	texture.loadFromFile("graphics/player_idle A_B_C.png");
	animation.SetTarget(&sprite);
	AnimationClip IdleClip;

	IdleClip.id = "Idle";
	IdleClip.fps = 10;
	IdleClip.loopType = AnimationLoopTypes::Loop;
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(0, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(32, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(64, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(96, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(128, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(160, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(192, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(224, 0, 32, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(0, 32, 32, 32)));
	animation.AddClip(IdleClip);
	IdleClip.frames.clear();

	texture.loadFromFile("graphics/player_climb_dangling_walk.png");

	animation.SetTarget(&sprite);
	AnimationClip clip;

	clip.id = "Idle";
	clip.fps = 10;
	clip.loopType = AnimationLoopTypes::Loop;
	clip.frames.push_back(AnimationFrame(texture, IntRect(0, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(32, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(64, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(96, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(128, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(160, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(192, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(224, 0, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(0, 32, 32, 32)));
	animation.AddClip(clip);
	clip.frames.clear();

	clip.id = "Walk";
	clip.fps = 10;
	clip.loopType = AnimationLoopTypes::Loop;
	
	clip.frames.push_back(AnimationFrame(texture, IntRect(32, 96, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(64, 96, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(96, 96, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(128, 96, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(160, 96, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(192, 96, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(224, 96, 32, 32)));

	clip.frames.push_back(AnimationFrame(texture, IntRect(0, 128, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(32, 128, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(64, 128, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(96, 128, 32, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(128, 128, 32, 32)));
	animation.AddClip(clip);
	clip.frames.clear();

	animation.Play("Idle");
}

void Player::Spawn(IntRect arena, Vector2i res)
{
	this->arena = arena;
	resolution = res;

	position.x = arena.width * 0.5;
	position.y = arena.height * 0.5;
	sprite.setPosition(position.x, position.y);
}

FloatRect Player::GetGobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotation() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

void Player::Update(float dt)
{
	animation.Update(dt);	


	float v = 0;
	float h = InputMgr::GetAxis(Axis::HorizontalRight);

	if (h > 0)
	{
		animation.Play("Walk");
	}
	else if(h < 0)
	{
		sprite.setScale(-1.f, 1.f);
		animation.Play("Walk");
	}
	else if( h == 0)
	{
		animation.Play("Idle");
	}


	Vector2f dir(h, v);
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 0)
	{
		dir /= length;
	}
	
	position += dir * speed * dt;
	sprite.setPosition(position);

}

void Player::Draw(RenderWindow &window)
{
	window.draw(sprite);
}
