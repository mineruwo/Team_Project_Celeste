#include "Player.h"
#include "../Utils/InputMgr.h"
#include "../Utils/Utils.h"
#include "../Utils/repidcw.h"
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

	rapidcsv::Document clips("data_tables/animations/player/player_animation_clips.csv");

	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexure = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		std::vector<int> colX = frames.GetColumn<int>("X");
		std::vector<int> colY = frames.GetColumn<int>("Y");

		int totalFrames = colTexure.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texMap.find(colTexure[i]) == texMap.end())
			{
				auto &ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j]), Vector2f(colX[j], colY[j])));
		}
		animation.AddClip(clip);
	}

	animation.Play("Idle");
	position = sprite.getPosition();


	/*texture.loadFromFile("graphics/player_idle A_B_C.png");
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

	texture.loadFromFile("graphics/player_climb_dangling_walk.png");

	animation.SetTarget(&sprite);
	AnimationClip clipClimb;

	clipClimb.id = "Climb";
	clipClimb.fps = 10;
	clipClimb.loopType = AnimationLoopTypes::Loop;

	clipClimb.frames.push_back(AnimationFrame(texture, IntRect(32, 96, 32, 32), Vector2f(16, 32)));


	animation.Play("Idle");
	position = sprite.getPosition();*/

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
				충돌 처리
==========================================*/



void Player::Crash(std::vector<Wall *> walls)
{
	for (auto& c : isCollision)
	{
		c = false;
	}

	for (auto v : walls)
	{
		if (floorHitbox.getGlobalBounds().intersects(v->GetWallRect()))
		{
			Pivots pivot = Utils::CollisionDir(v->GetWallRect(), floorHitbox.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				//왼쪽
				position.x += (v->GetWallRect().left + v->GetWallRect().width) - (floorHitbox.getGlobalBounds().left);
				isCollision[2] = true;
				break;

			case Pivots::RC:
				position.x -= (floorHitbox.getGlobalBounds().left + floorHitbox.getGlobalBounds().width) - (v->GetWallRect().left);
				isCollision[3] = true;
				break;

			case Pivots::CT:
				position.y += (v->GetWallRect().top + v->GetWallRect().height) - (floorHitbox.getGlobalBounds().top);
				break;

			case Pivots::CB:
				position.y -= (floorHitbox.getGlobalBounds().top + floorHitbox.getGlobalBounds().height) - (v->GetWallRect().top);
				gravityV = 0.f;
				break;

			defalut:
				break;
			}
			sprite.setPosition(position);
		}
	}

}

/*========================================
	키 입력에 따른 플레이어의 애니메이션 
==========================================*/
void Player::UpdateInput()
{
	if (InputMgr::GetKeyDown(Keyboard::Right)) //오른쪽 이동
	{
		action = PlayerAction::MOVE;
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
		animation.Play("Idle");
		animation.PlayQueue("Idle");
	}
	if (InputMgr::GetKeyUp(Keyboard::Left))
	{
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
		if (isRight)
		{
			sprite.setScale(4.f, 3.f);
		}
		else if (!isRight)
		{
			sprite.setScale(-4.f, 3.f);
		}
						
	}
	if (InputMgr::GetKeyUp(Keyboard::Down))
	{
		if (isSeizeWall == true)
		{

		}
		else if(isRight)
		{
			sprite.setScale(4.f, 4.f);
		}
		else if (!isRight)
		{
			sprite.setScale(-4.f, 4.f);
		}

	}
	if (InputMgr::GetKeyDown(Keyboard::C)) //점프
	{
		isJump = true;
		animation.Play("Jump");
		prePosition.y = position.y;

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
		prePosition.x = position.x;
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
	/*if (gravityV == 0)
	{
		isJump = true;
	}
	else
	{
		isJump = false;
	}*/

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
		if (isSeizeWall == false)
		{
			if (dt < 1.f)
			{
				if (isJump = true)
				{
					position.y -= dt * speed * 2.f;
					isFalling = true;
					/*if (position.y > 1)
					{
						position.y -= dt * speed * 3.f;
					}*/
				}
			}
		}
		/*else if (isSeizeWall == true)
		{
			isFalling = true;
			position.y *= -1.f;
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
		
		// 다시 체크
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
				dashCount = START_DASH;
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
				dashCount = START_DASH;
				isFalling = true;
			}
		}
		else if (InputMgr::GetKey(Keyboard::Up))
		{			
			//isJump = true;
			isFalling = true;
			dashCount--;
			position.y -= dt * speed * 3.f;
		}
		else if (InputMgr::GetKey(Keyboard::Down))
		{
			//isJump = true;
			isFalling = true;
			dashCount--;
			position.y += dt * speed * 3.f;
		}		
	}	
	if (InputMgr::GetKey(Keyboard::Z))
	{
		if (isCollision[2] || isCollision[3])
		{
			position.x = prePosition.x;
			isFalling = false;
			if (InputMgr::GetKey(Keyboard::Up))
			{
				position.y -= dt * speed;
			}
			if (InputMgr::GetKey(Keyboard::Down))
			{
				position.y += dt * speed;
			}
			if (dt > 6.f)
			{
				position.y += dt * speed;
			}
		}
		else
		{
			isFalling = true;
		}
		//isFalling = true;
	}
	if (InputMgr::GetKeyUp(Keyboard::Z))
	{
		isFalling = true;
	}
	//충돌 처리

	Crash(walls);
	/*for (auto v : walls)
	{
		if (floorHitbox.getGlobalBounds().intersects(v->GetWallRect()))
		{
			Pivots pivot = Utils::CollisionDir(v->GetWallRect(), floorHitbox.getGlobalBounds());


			switch (pivot)
			{
			case Pivots::LC:
				//왼쪽
				position.x += (v->GetWallRect().left + v->GetWallRect().width) - (floorHitbox.getGlobalBounds().left);
				break;

			case Pivots::RC:
				position.x -= (floorHitbox.getGlobalBounds().left + floorHitbox.getGlobalBounds().width) - (v->GetWallRect().left);
				break;

			case Pivots::CT:
				position.y += (v->GetWallRect().top + v->GetWallRect().height) - (floorHitbox.getGlobalBounds().top);
				break;

			case Pivots::CB:
				isFloor = true;
				position.y -= (floorHitbox.getGlobalBounds().top + floorHitbox.getGlobalBounds().height) - (v->GetWallRect().top);
				gravityV = 0.f;				
				break;

			defalut:
				break;
			}
			sprite.setPosition(position);
		}
	}*/

	sprite.setPosition(position);

	bodyPosition.x = position.x;
	bodyPosition.y = position.y - 10.f;
	bodyHitbox.setPosition(bodyPosition);

	floorPosition.x = position.x;
	floorPosition.y = position.y;
	floorHitbox.setPosition(floorPosition);

	animation.Update(dt);
}

FloatRect Player::GetFloorGobalBound() const
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