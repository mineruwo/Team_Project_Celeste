#include "Player.h"
#include "../Utils/InputMgr.h"
#include "../Utils/Utils.h"
#include "../Utils/repidcw.h"
#include <iostream>

/*==============================
		 플레이어 생성자
================================*/
Player::Player()
	:speed(START_SPEED), gravity(GRAVITY), isJump(false), isDash(false), isCatch(false)
	, isFalling(true), isSeizeWall(false), isRight(true), isFloor(false),
	jumpTime(0.f), jumpHeight(0), jumpPower(50.f)
{
}

/*==============================
		 플레이어 초기화
================================*/
void Player::Init()
{
	sprite.setPosition(900, 0);
	sprite.setScale(CharacSize, CharacSize);
	sprite.setOrigin(Vector2f(16 * CharacSize, 32 * CharacSize));

	//몸 히트 박스
	bodyHitbox.setFillColor(Color::Green);
	bodyHitbox.setSize(Vector2f(8.f * CharacSize, 10.f * CharacSize));
	bodyHitbox.setOrigin(bodyHitbox.getGlobalBounds().width*0.5, bodyHitbox.getGlobalBounds().height * 0.5);
	bodyPosition.x = position.x + 2.f;
	bodyPosition.y = position.y - 15.f;
	bodyHitbox.setPosition(bodyPosition);


	//바닥 히트 박스
	floorHitbox.setFillColor(Color::Red);
	floorHitbox.setSize(Vector2f(8.f * CharacSize, 2.f* CharacSize));
	floorHitbox.setOrigin(floorHitbox.getGlobalBounds().width * 0.5, floorHitbox.getGlobalBounds().height * 0.5);
	floorPosition.x = position.x + 2.f;
	floorPosition.y = position.y - 2.f;
	floorHitbox.setPosition(floorPosition);

	animation.SetTarget(&sprite);

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
				auto& ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j]), Vector2f(colX[j], colY[j])));
		}
		animation.AddClip(clip);
	}

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
				충돌 처리
==========================================*/



void Player::Crash(std::vector<Wall*> walls)
{
	for (auto& c : isCollision)
	{
		c = false;
	}

	for (auto v : walls)
	{

		/*if (floorHitbox.getGlobalBounds().intersects(v->GetWallRect()))
		{



		}*/
		if (floorHitbox.getGlobalBounds().intersects(v->GetWallRect()))
		{
			Pivots pivot = Utils::CollisionDir(v->GetWallRect(), floorHitbox.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				//오른쪽
				position.x += (v->GetWallRect().left + v->GetWallRect().width) - (floorHitbox.getGlobalBounds().left);
				isCollision[3] = true;
				break;
				//왼쪽
			case Pivots::RC:
				position.x -= (floorHitbox.getGlobalBounds().left + floorHitbox.getGlobalBounds().width) - (v->GetWallRect().left);
				isCollision[2] = true;
				break;
			case Pivots::CT:
				position.y += (v->GetWallRect().top + v->GetWallRect().height) - (floorHitbox.getGlobalBounds().top);
				isCollision[1] = true;
				break;

			case Pivots::CB:
				position.y -= (floorHitbox.getGlobalBounds().top + floorHitbox.getGlobalBounds().height) - (v->GetWallRect().top);
				isCollision[0] = true;
				gravityV = 0.f;
				break;

			defalut:
				break;
			}
			sprite.setPosition(position);
		}
	}
}

void Player::Jump(float dt)
{
	/*if (!isJump) return;
	float k = jumpPower * (3.f / 2.f);
	jumpHeight += (jumpTime * jumpTime - jumpPower * jumpTime) / k * 0.03f;

	jumpTime += 0.04f;

	if (jumpTime > k)
	{
		jumpTime = 0;
		jumpHeight = 0;
		isJump = false;
	}*/
	
	if (InputMgr::GetKey(Keyboard::C))
	{
		if (isRight == true)
		{
			position.y -= dt * speed * 2.f;
		}
		else if (isRight == false)
		{
			position.y -= dt * speed * 2.f;
		}
	}
}

void Player::Move(float dt)
{
	
	if (InputMgr::GetKey(Keyboard::Right))
	{
		position.x += dt * speed;
	}
	if (InputMgr::GetKey(Keyboard::Left))
	{
		position.x -= dt * speed;
	}
}

/*========================================
	키 입력에 따른 플레이어의 애니메이션
==========================================*/
void Player::UpdateInput()
{
	if (InputMgr::GetKeyDown(Keyboard::Right)) //오른쪽 이동
	{
		moveMent = PlayerAction::MOVE;
		isRight = true;
		sprite.setScale(CharacSize, CharacSize);
		animation.Play("Move");
	}
	if (InputMgr::GetKeyDown(Keyboard::Left)) //왼쪽 이동
	{
		moveMent = PlayerAction::MOVE;
		isRight = false;
		sprite.setScale(-CharacSize, CharacSize);
		animation.Play("Move");
	}
	if (InputMgr::GetKeyUp(Keyboard::Right) || InputMgr::GetKeyUp(Keyboard::Left))
	{
		moveMent = PlayerAction::IDLE;
		animation.Play("Idle");
		animation.PlayQueue("Idle");
	}
	if (InputMgr::GetKeyDown(Keyboard::Up))
	{
		moveMent = PlayerAction::LOOKUP;
		animation.Play("Lookup");
		animation.PlayQueue("Idle");
	}
	if (InputMgr::GetKeyDown(Keyboard::Down))
	{
		if (isRight)
		{
			sprite.setScale(CharacSize, CharacSize - 1.f);
		}
		else if (!isRight)
		{
			sprite.setScale(-CharacSize, CharacSize - 1.f);
		}
	}
	if (InputMgr::GetKeyUp(Keyboard::Down))
	{
		if (isRight)
		{
			sprite.setScale(CharacSize, CharacSize);
		}
		else if (!isRight)
		{
			sprite.setScale(-CharacSize, CharacSize);
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::C)) //점프
	{
		moveMent = PlayerAction::JUMP;		
		isJump = true;

		animation.Play("Jump");
		prePosition.y = position.y;

		if (InputMgr::GetKeyDown(Keyboard::Right) || InputMgr::GetKeyDown(Keyboard::Left))
		{
			animation.PlayQueue("Move");
		}
		moveMent = PlayerAction::IDLE;
	}

	if (InputMgr::GetKeyDown(Keyboard::X)) //대쉬
	{
		moveMent = PlayerAction::DASH;
		isDash = true;
		
		deshDir.x = position.x;
		deshDir.y = position.y;

		//animation.Play();
		if (InputMgr::GetKeyDown(Keyboard::Right) || InputMgr::GetKeyDown(Keyboard::Left))
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
		moveMent = PlayerAction::Climb;
		animation.Play("Climb");
		prePosition.x = position.x;
		if (InputMgr::GetKeyDown(Keyboard::Up) || InputMgr::GetKeyDown(Keyboard::Down))
		{
			animation.Play("Climb");
		}
	}

}

/*============================================
	키 입력에 따른 플레이어의 액션 업데이트
==============================================*/
void Player::Update(float dt, std::vector<Wall*> walls)
{
	UpdateInput();
	// 중 력
	if (isFalling == true)
	{
		gravityV += gravity * dt;
		position.y += gravityV * dt;
	}
	// 점 프
	/*if (isJump == true)
	{
		if (isRight)
		{
			position.y -= dt * speed * 2.f;
		}
		else if (!isRight)
		{
			position.y -= dt * speed * 2.f;
		}
	}*/
	
	switch (moveMent)
	{
	case PlayerAction::IDLE:

		break;
	case PlayerAction::MOVE:
		Move(dt);
		break;
	case PlayerAction::JUMP:
			//isJump = true;
		Jump(dt);		
		break;
	case PlayerAction::DASH:

		break;
	case PlayerAction::LOOKUP:
		break;
	case PlayerAction::Climb:
		break;
	default:
		break;
	}
	// 상하좌우이동
	
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
	


	//if (!isJump && InputMgr::GetKey(Keyboard::C))
	//{
	//	/*if (isCollision[0])
	//	{
	//		if (dt < 1.f)
	//		{
	//			if (isJump = true)
	//			{
	//				position.y -= dt * speed * 2.f;
	//				isFalling = false;

	//			}
	//		}
	//	}*/
	//	if (isSeizeWall == false)
	//	{
	//		if (dt < 1.f)
	//		{
	//			if (isJump = true)
	//			{
	//				position.y -= dt * speed * 2.f;
	//				isFalling = true;
	//				/*if (position.y > 1)
	//				{
	//					position.y -= dt * speed * 3.f;
	//				}*/
	//			}
	//		}
	//	}
	//	/*else if (isSeizeWall == true)
	//	{
	//		isFalling = true;
	//		position.y *= -1.f;
	//	}*/

	//}


	//대쉬
	if (InputMgr::GetKeyDown(Keyboard::X) || InputMgr::GetKey(Keyboard::X))
	{
		if (isDash == true)
		{
			isFalling = false;
			if (isRight == true)
			{
				position.x += dt * speed * 3.f;
			}
			else if (isRight == false)
			{
				position.x -= dt * speed * 3.f;
			}
		}		
		else 
		{
			isDash = false;
		}		
	}


	//if ((InputMgr::GetKeyDown(Keyboard::X) || InputMgr::GetKey(Keyboard::X)))
	//{
	//	isDash = false;
	//	/*if (isCollision[1])
	//	{
	//		if (isRight == true)
	//		{
	//			if (position.x < deshDir.x + 200)
	//			{
	//				isFalling = false;
	//				position.x += dt * speed * 3.f;
	//			}
	//			else
	//			{
	//				isFalling = true;
	//			}
	//		}
	//		else if (isRight == false)
	//		{
	//			if (position.x > deshDir.x - 200)
	//			{
	//				isFalling = false;
	//				position.x -= dt * speed * 3.f;
	//			}
	//			else
	//			{
	//				isFalling = true;
	//			}
	//		}
	//	}*/		
	//	/*if (InputMgr::GetKey(Keyboard::Right))
	//	{
	//		if (position.x < deshDir.x + 200)
	//		{
	//			isFalling = false;
	//			position.x += dt * speed * 3.f;
	//		}
	//	}
	//	else if (InputMgr::GetKey(Keyboard::Left))
	//	{
	//		if (position.x > deshDir.x - 200)
	//		{
	//			isFalling = false;
	//			position.x -= dt * speed * 3.f;
	//		}
	//	}
	//	else if (InputMgr::GetKey(Keyboard::Up))
	//	{
	//		isFalling = true;
	//		position.y -= dt * speed * 3.f;
	//	}
	//	else if (InputMgr::GetKey(Keyboard::Down))
	//	{
	//		isFalling = true;
	//		position.y += dt * speed * 3.f;
	//	}*/
	//}
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

	Crash(walls);

	sprite.setPosition(position);

	bodyPosition.x = position.x + 2.f;
	bodyPosition.y = position.y - 15.f;
	bodyHitbox.setPosition(bodyPosition);

	floorPosition.x = position.x + 2.f;
	floorPosition.y = position.y - 2.f;
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
void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	window.draw(floorHitbox);
	window.draw(bodyHitbox);
	

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