#include "Player.h"
#include "../Utils/InputMgr.h"
#include "../Utils/Utils.h"
#include <iostream>

/*==============================
		 플레이어 생성자
================================*/
Player::Player()
	:speed(START_SPEED), gravity(GRAVITY), isJump(true), isDash(false), isCatch(false)
	, isFalling(true), isSeizeWall(false), isRight(true), isFloor(false), dashCount(START_DASH)
{	
}

/*==============================
	     플레이어 초기화
================================*/
void Player::Init()
{
	sprite.setPosition(900,0);
	sprite.setScale(4.f, 4.f);
	sprite.setOrigin(Vector2f(16 *4.f, 32 * 4.f));
	
	//몸 히트 박스
	bodyHitbox.setFillColor(Color::Green);
	bodyHitbox.setSize(Vector2f(8.f * CharacSize, 10.f * CharacSize));
	bodyHitbox.setOrigin(40 * 0.5 , 40);
	bodyPosition.x = position.x;
	bodyPosition.y = position.y - 6.f;
	bodyHitbox.setPosition(bodyPosition);
	
	
	//바닥 히트 박스
	floorHitbox.setFillColor(Color::Red);
	floorHitbox.setSize(Vector2f(8.f * CharacSize, 10.f));
	floorHitbox.setOrigin(40 * 0.5, 10);
	floorPosition.x = position.x;
	floorPosition.y = position.y;
	floorHitbox.setPosition(floorPosition);

	texture.loadFromFile("graphics/player_idle A_B_C.png");
	animation.SetTarget(&sprite);
	AnimationClip IdleClip;

	IdleClip.id = "Idle";
	IdleClip.fps = 10;
	IdleClip.loopType = AnimationLoopTypes::Loop;
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(0, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(32, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(64, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(96, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(128, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(160, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(192, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(224, 0, 32, 32), Vector2f(16, 32)));
	IdleClip.frames.push_back(AnimationFrame(texture, IntRect(0, 32, 32, 32), Vector2f(16, 32)));
	animation.AddClip(IdleClip);
	IdleClip.frames.clear();

	texture.loadFromFile("graphics/player_climb_dangling_walk.png");

	animation.SetTarget(&sprite);
	AnimationClip clip;

	clip.id = "Walk";
	clip.fps = 10;
	clip.loopType = AnimationLoopTypes::Loop;
	
	clip.frames.push_back(AnimationFrame(texture, IntRect(32, 96, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(64, 96, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(96, 96, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(128, 96, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(160, 96, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(192, 96, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(224, 96, 32, 32), Vector2f(16, 32)));

	clip.frames.push_back(AnimationFrame(texture, IntRect(0, 128, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(32, 128, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(64, 128, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(96, 128, 32, 32), Vector2f(16, 32)));
	clip.frames.push_back(AnimationFrame(texture, IntRect(128, 128, 32, 32), Vector2f(16, 32)));
	animation.AddClip(clip);
	clip.frames.clear();

	texture.loadFromFile("graphics/player_JumpCarry_JumpFast_JumpSlow_sitDown.png");

	animation.SetTarget(&sprite);
	AnimationClip clipJump;

	clipJump.id = "Jump";
	clipJump.fps = 10;
	clipJump.loopType = AnimationLoopTypes::Single;

	clipJump.frames.push_back(AnimationFrame(texture, IntRect(128, 0, 32, 32), Vector2f(16, 32)));
	clipJump.frames.push_back(AnimationFrame(texture, IntRect(160, 0, 32, 32), Vector2f(16, 32)));
	clipJump.frames.push_back(AnimationFrame(texture, IntRect(192, 0, 32, 32), Vector2f(16, 32)));
	clipJump.frames.push_back(AnimationFrame(texture, IntRect(224, 0, 32, 32), Vector2f(16, 32)));
	
	animation.AddClip(clipJump);
	clipJump.frames.clear();

	animation.Play("Idle");

	position = sprite.getPosition();

}
/*void Player::Spawn(IntRect arena, Vector2i res)
{
	this->arena = arena;
	resolution = res;

	position.x = arena.width * 0.5;
	position.y = arena.height * 0.5;
	sprite.setPosition(position.x, position.y);

	
}*/
/*========================================
	키 입력에 따른 플레이어의 애니메이션 
==========================================*/
void Player::UpdateInput()
{
	if (InputMgr::GetKeyDown(Keyboard::Right)) //오른쪽 이동
	{
		isRight = true;
		sprite.setScale(4.f, 4.f);
		animation.Play("Walk");		
	}
	if (InputMgr::GetKeyDown(Keyboard::Left)) //왼쪽 이동
	{
		isRight = false;
		sprite.setScale(-4.f, 4.f);
		animation.Play("Walk");		
	}
	if (InputMgr::GetKeyUp(Keyboard::Right)) 
	{
		//sprite.setScale(4.f, 4.f);
		animation.Play("Idle");
		animation.PlayQueue("Idle");
	}
	if (InputMgr::GetKeyUp(Keyboard::Left))
	{
		//sprite.setScale(-4.f, 4.f);
		animation.Play("Idle");
		animation.PlayQueue("Idle");
	}
	if (InputMgr::GetKeyDown(Keyboard::Up))
	{
		//위 올려보는 애니메이션
		//animation.Play("");
	}
	if (InputMgr::GetKeyDown(Keyboard::Down))
	{
		isCatch = false;
		sprite.setScale(4.f, 3.f);				
	}
	if (InputMgr::GetKeyUp(Keyboard::Down))
	{
		if (isSeizeWall == true)
		{

		}
		else
		{
			sprite.setScale(4.f, 4.f);
		}

	}
	if (InputMgr::GetKeyDown(Keyboard::C)) //점프
	{
		isJump = true;
		animation.Play("Jump");
		if (InputMgr::GetKeyDown(Keyboard::Right) || InputMgr::GetKeyDown(Keyboard::Left))
		{
			animation.PlayQueue("Walk");
		}
		else if (InputMgr::GetKeyUp(Keyboard::Right) || InputMgr::GetKeyUp(Keyboard::Left))
		{
			animation.Play("Idle");
		}	
	}

	if (InputMgr::GetKeyDown(Keyboard::X)) //대쉬
	{
		isDash = true;
		dashCount = START_DASH;
		deshDir.x = position.x;
		deshDir.y = position.y;
		
		//animation.Play();
		if (InputMgr::GetKeyDown(Keyboard::Right)|| InputMgr::GetKeyDown(Keyboard::Left))
		{
			animation.PlayQueue("Walk");
		}
		else if (InputMgr::GetKeyUp(Keyboard::Right) || InputMgr::GetKeyUp(Keyboard::Left))
		{
			animation.Play("Idle");
		}
		animation.PlayQueue("Idle");
		
	}
	if (InputMgr::GetKeyDown(Keyboard::Z)) // 벽잡기
	{
		
	}

}

/*============================================
	키 입력에 따른 플레이어의 액션 업데이트
==============================================*/
void Player::Update(float dt, std::vector<Wall *> walls)
{
	UpdateInput();
	// 중 력
	if (isFalling == true)
	{
		gravityV += gravity * dt;
		position.y += gravityV * dt;
	}
	if (dashCount < 0)
	{
		isDash = false;
	}
	else if (dashCount == START_DASH)
	{
		isDash = true;
	}

	// 상하좌우이동
	if (InputMgr::GetKey(Keyboard::Right))
	{
		position.x += dt * speed;
	}
	if (InputMgr::GetKey(Keyboard::Left))
	{
		position.x -= dt * speed;
	}
	if (InputMgr::GetKey(Keyboard::Up))
	{
		if (isSeizeWall == true)
		{
			position.y -= dt * speed;
		}
		else
		{
			position.y;
		}
	}
	if (InputMgr::GetKey(Keyboard::Down))
	{
		if (isSeizeWall == true)
		{
			position.y += dt * speed;
		}
		else
		{
			position.y;
		}
	}

	// 점프 이동
	// 바닥에 닿았을 때만 작동되도록

	if ( isJump && InputMgr::GetKey(Keyboard::C))
	{

		if (dt < 1.f)
		{
			if (isJump == true)
			{
				position.y -= dt * speed * 2.f;
				isFalling = true;
				/*if (position.y > 1)
				{
					position.y -= dt * speed * 3.f;
				}*/
			}

		}

		/*if (position.x )
		{
			position.x *= -1.f;
		}*/

	}
	//대쉬
	if ((InputMgr::GetKeyDown(Keyboard::X) || InputMgr::GetKey(Keyboard::X)))
	{
		/*if (isRight == true)
		{
			if (position.x < deshDir.x + 200)
			{
				isFalling = false;
				position.x += dt * speed * 3.f;
			}
			else
			{
				isFalling = true;
			}
		}
		else if (isRight == false)
		{
			if (position.x > deshDir.x - 200)
			{
				isFalling = false;
				position.x -= dt * speed * 3.f;
			}
			else
			{
				isFalling = true;
			}
		}*/
		
		if (InputMgr::GetKey(Keyboard::Right))
		{
			if (position.x < deshDir.x + 200)
			{
				dashCount--;
				isFalling = false;
				position.x += dt * speed * 3.f;
			}
			else
			{
				isFalling = true;
			}
		}
		else if (InputMgr::GetKey(Keyboard::Left))
		{
			if (position.x > deshDir.x - 200)
			{
				dashCount--;
				isFalling = false;
				position.x -= dt * speed * 3.f;
			}
			else
			{
				isFalling = true;
			}
		}
		else if (InputMgr::GetKey(Keyboard::Up))
		{
			isJump = true;
			isFalling = true;
			dashCount--;
			position.y -= dt * speed * 3.f;
		}
		else if (InputMgr::GetKey(Keyboard::Down))
		{
			isJump = true;
			isFalling = true;
			dashCount--;
			position.y += dt * speed * 3.f;
		}		
	}	
	//충돌 처리
	for (auto v : walls)
	{
		if (floorHitbox.getGlobalBounds().intersects(v->GetWallRect()))
		{
			Pivots pivot = Utils::CollisionDir(v->GetWallRect(), sprite.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				position.x += (v->GetWallRect().left + v->GetWallRect().width) - (sprite.getGlobalBounds().left);
				break;

			case Pivots::RC:
				position.x -= (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) - (v->GetWallRect().left);
				break;

			case Pivots::CT:
				position.y += (v->GetWallRect().top + v->GetWallRect().height) - (sprite.getGlobalBounds().top);
				break;

			case Pivots::CB:
				isFloor = true;
				position.y -= (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) - (v->GetWallRect().top);
				gravityV = 0.f;				
				break;

			defalut:
				break;
			}
			sprite.setPosition(position);
		}
	}

	sprite.setPosition(position);

	bodyPosition.x = position.x;
	bodyPosition.y = position.y - 10.f;
	bodyHitbox.setPosition(bodyPosition);

	floorPosition.x = position.x;
	floorPosition.y = position.y;
	floorHitbox.setPosition(floorPosition);

	animation.Update(dt);
}

FloatRect Player::GetGobalBound() const
{
	return floorHitbox.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

Sprite Player::GetSprite() const
{
	return sprite;
}

/*==============================
		플레이어 그리기
================================*/
void Player::Draw(RenderWindow &window)
{	
	
	window.draw(floorHitbox);
	window.draw(bodyHitbox);
	window.draw(sprite);
	
}
/*===============================
작 성 자 : 최 윤 화
구 현 내 용 : 플레이어 동작 구현
작 성 일 : 2022 - 05 - 04
수 정 일 : 2022 - 05 - 06
 - 충돌처리 오류
 - 점프 키 구현
 - 대쉬 키 구현
=================================*/