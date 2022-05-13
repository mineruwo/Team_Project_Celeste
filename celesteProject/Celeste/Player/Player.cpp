#include "Player.h"
#include "../Utils/InputMgr.h"
#include "../Utils/Utils.h"
#include "../Utils/repidcw.h"
#include <math.h>
#include <iostream>

/*==============================
		 플레이어 생성자
================================*/
Player::Player()
	:speed(START_SPEED), isJump(false), isDash(false), isCatch(false)
	, isFalling(true), isSeizeWall(false), isRight(true), isFloor(false),
	jumpTime(0.f), jumpSpeed(START_JUMPSPEED), fallingSpeed(0.f)
{
}

/*==============================
		 플레이어 초기화
================================*/
void Player::Init()
{
	position.x = 815.f;
	position.y = 511.f;
	sprite.setPosition(position); //815, 511
	sprite.setScale(CharacSize, CharacSize);
	sprite.setOrigin(Vector2f((16.f * CharacSize) * 0.5f, 32.f * CharacSize));

	//몸 히트 박스
	bodyHitbox.setFillColor(Color::Transparent);
	bodyHitbox.setOutlineColor(Color::Yellow);
	bodyHitbox.setOutlineThickness(1.f);
	bodyHitbox.setSize(Vector2f(8.f * CharacSize, 10.f * CharacSize));
	bodyHitbox.setOrigin(Vector2f((8.f * CharacSize) * 0.5f, 10.f * CharacSize));
	//bodyHitbox.setPosition(position);

	//바닥 히트 박스
	floorHitbox.setFillColor(Color::Red);
	floorHitbox.setSize(Vector2f(8.f * CharacSize, 2.f * CharacSize));
	floorHitbox.setOrigin(Vector2f((8.f * CharacSize) * 0.5f, 2.f * CharacSize));

	AnimationInit();
	animation.Play("Idle");
	//position = sprite.getPosition();
}

//void Player::Spawn(IntRect arena, Vector2i res)
//{
//	this->arena = arena;
//	resolution = res;
//
//	position.x = arena.width * 0.5;
//	position.y = arena.height * 0.5;
//	sprite.setPosition(position.x, position.y);
//}

/*============================================
	키 입력에 따른 플레이어의 액션 업데이트
==============================================*/
void Player::Update(float dt, std::vector<Wall*> walls)
{
	isFalling = moveMent != PlayerAction::DASH && !isFloor;

	// 중 력
	if (isFalling)
	{
		gravity += GRAVITY * dt;
		position.y += gravity * dt;
	}
	else
	{
		gravityV = 0.f;
	}
	if (gravityV > 980.f) //최대 중력 조절
	{
		gravityV = 980.f;
	}

	//충돌 처리 업데이트
	UpdateCrash(walls);

	//std::cout << (int)moveMent << std::endl;
	switch (moveMent)
	{
	case PlayerAction::IDLE:
		break;
	case PlayerAction::MOVE:
		Move(dt);
		break;
	case PlayerAction::JUMP:
		Jump(dt);
		break;
	case PlayerAction::DASH:
		Dash(dt);
		break;
	case PlayerAction::LOOKUP:
		break;
	case PlayerAction::LOOKDOWN:
		break;
	case PlayerAction::CLIMB:
		Climb(dt);
		break;
	default:
		break;
	}

	statusDT = dt;

	animation.Update(dt);
	UpdateAnimation(dt);


	sprite.setPosition(position);
	bodyHitbox.setPosition(position);
	floorHitbox.setPosition(position);

}

/*========================================
				충돌 처리
==========================================*/
void Player::UpdateCrash(std::vector<Wall*> walls)
{
	for (auto& c : isCollision)
	{
		c = false;
	}
	isFloor = false;
	for (auto v : walls)
	{
		// 플레이어의 origin를 이용
		// x > y 일경우 (위/아래)으로 보냄, x < y일 경우 (오른쪽/왼쪽)으로 보냄

		if (bodyHitbox.getGlobalBounds().intersects(v->GetWallRect()))
		{
			float wallTop = v->GetWallRect().top;
			float wallBottom = v->GetWallRect().top + v->GetWallRect().height;
			float wallLeft = v->GetWallRect().left;
			float wallRight = v->GetWallRect().left + v->GetWallRect().width;


			float playerTop = bodyHitbox.getGlobalBounds().top;
			float playerBottom = bodyHitbox.getGlobalBounds().top + bodyHitbox.getGlobalBounds().height;
			float playerLeft = bodyHitbox.getGlobalBounds().left;
			float playerRight = bodyHitbox.getGlobalBounds().left + bodyHitbox.getGlobalBounds().width;

			/*float playerTop = bodyHitbox.getPosition().y - bodyHitbox.getGlobalBounds().height;
			float playerBottom = bodyHitbox.getPosition().y;
			float playerLeft = bodyHitbox.getGlobalBounds().left;
			float playerRight = bodyHitbox.getPosition().x + bodyHitbox.getGlobalBounds().width * 0.5;*/

			float playerX = bodyHitbox.getPosition().x;
			float playerY = bodyHitbox.getPosition().y - bodyHitbox.getGlobalBounds().height * 0.5;
			Vector2f posi = bodyHitbox.getPosition();

			//LT
			if (wallLeft > playerX && wallTop > playerY)
			{
				isFloor = true;
				//X가 큰 범위 인 경우 위로 보냄
				if (abs(wallTop - playerBottom) < abs(wallLeft - playerRight))
				{
					//std::cout << v->GetId() << "LTX충돌" << std::endl;
					posi.y = wallTop + 1.f;
					//posi.y = wallTop + 1.f;
					//gravityV = 0.f;
				}
				//Y가 큰 범위 인 경우 옆으로 보냄
				else if (abs(wallTop - playerBottom) > abs(wallLeft - playerRight))
				{
					//std::cout << v->GetId() << "LTY충돌" << std::endl;
					posi.x = wallLeft - bodyHitbox.getGlobalBounds().width * 0.5;
				}
				//X와 Y 값이 동일한 경우
				else
				{
					posi.y -= abs(wallTop - playerBottom);
					posi.x -= abs(wallLeft - playerRight);
					posi.y += 1.f;
				}
			}

			//CT
			if (wallLeft < playerX && wallRight > playerX && wallTop > playerY)
			{
				isCollision[2] = true;
				isFloor = true;
				std::cout << v->GetId() << "CT충돌" << std::endl;
				posi.y = wallTop + 1.f;
				//gravityV = 0.f;
			}
			//RT
			if (wallRight < playerX && wallTop > playerY)
			{
				isFloor = true;

				//std::cout << v->GetId() << "RT충돌" << std::endl;
				//X
				if (abs(wallTop - playerBottom) < abs(wallLeft - playerRight))
				{
					posi.y = wallTop + 1.f;
					//gravityV = 0.f;
				}
				//Y
				else if (abs(wallTop - playerBottom) > abs(wallLeft - playerRight))
				{
					posi.x = wallLeft + bodyHitbox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					posi.x += abs(wallLeft - wallRight);
					posi.y -= abs(wallTop - wallBottom);
					posi.y += 1.f;
				}
			}

			//LC
			if (wallLeft > playerX && wallTop < playerY && wallBottom > playerY)
			{
				isCollision[2] = true;
				std::cout << v->GetId() << "LC충돌" << std::endl;
				posi.x = wallLeft - bodyHitbox.getGlobalBounds().width * 0.5f;
			}
			//RC
			if (wallRight < playerX && wallTop < playerY && wallBottom > playerY)
			{
				isCollision[0] = true;
				//std::cout << "RC충돌" << std::endl;
				posi.x = wallRight + bodyHitbox.getGlobalBounds().width * 0.5f;
			}
			//LB
			if (wallBottom < playerY && wallLeft > playerX)
			{
				//std::cout << v->GetId() << "LB충돌" << std::endl;
				//X
				if (abs(wallBottom - playerTop) < abs(wallLeft - playerRight))
				{
					posi.y = wallBottom + bodyHitbox.getGlobalBounds().height;
				}
				//Y
				else if (abs(wallBottom - playerTop) > abs(wallLeft - playerRight))
				{
					posi.x = wallLeft - bodyHitbox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					posi.x -= abs(wallLeft = playerRight);
					posi.y += abs(wallBottom - playerTop);
				}
			}
			//CB
			if (wallLeft < playerX && wallRight > playerX && wallBottom < playerY)
			{
				isCollision[3] = true;
				//std::cout << v->GetId() << "CB충돌" << std::endl;
				posi.y = wallBottom + bodyHitbox.getGlobalBounds().height;
			}
			//RB
			if (wallBottom < playerY && wallRight < playerX)
			{
				//std::cout << v->GetId() << "RB충돌" << std::endl;
				//X
				if (abs(wallBottom - playerTop) < abs(wallLeft - playerRight))
				{
					posi.y = wallBottom + bodyHitbox.getGlobalBounds().height;
				}
				//Y
				else if (abs(wallBottom - playerTop) > abs(wallLeft - playerRight))
				{
					posi.x = wallRight + bodyHitbox.getGlobalBounds().width * 0.5f;
				}
				else
				{
					posi.x += abs(wallLeft - playerRight);
					posi.y += abs(wallBottom - playerTop);
				}
			}
			bodyHitbox.setPosition(posi);
			position = posi;
		}
	}
}


/*===========================
		점프 액션 코드
=============================*/
void Player::Jump(float dt)
{
	isFalling = false;
	if (isJump == true)
	{
		jumpSpeed -= GRAVITY * dt;
		position.y -= jumpSpeed * dt;
		if (jumpSpeed < 0.f)
		{
			isJump = false;
			jumpSpeed = START_JUMPSPEED;
		}
	}
	else if (isJump == false)
	{
		fallingSpeed += GRAVITY * dt;
		if (fallingSpeed > 1000.f)
		{
			fallingSpeed = 1000.f;
		}
	}

	/*if (dt < 1.f)
	{

		position.y -= dt * speed * 3.f;
		if (position.y < 200.f)
		{
			isJump = false;
		}

	}*/
}

/*===========================
	  움직이는 액션 코드
=============================*/
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

/*===========================
	  움직이는 대쉬 코드
=============================*/
void Player::Dash(float dt)
{
	deshDir = position;

	if (isDash = true)
	{
		if (isRight == true)
		{
			position.x += dt * speed * 2.f;
		}
		else if (isRight == false)
		{
			position.x -= dt * speed * 2.f;
		}
		if (position.x < deshDir.y + 200 || position.x > deshDir.y - 200)
		{
			isDash = false;
		}
	}


	/*if (position.x < deshDir.x + 200)
	{
		if (isRight == true)
		{
			position.x += dt * speed * 3.f;
		}
	}
	else if (position.x > deshDir.x - 200)
	{
		if (isRight == false)
		{
			position.x -= dt * speed * 3.f;
		}
	}
	else if (position.y < deshDir.y + 200)
	{
		if (isUp == true)
		{
			position.y -= dt * speed * 3.f;
		}
	}
	else if (position.y > deshDir.y - 200)
	{
		if (isUp == false)
		{
			position.y += dt * speed * 3.f;
		}
	}*/
}

/*===========================
	  벽타는 액션 코드
=============================*/
void Player::Climb(float dt)
{
	if (isCollision[2] || isCollision[3])
	{
		if (InputMgr::GetKey(Keyboard::Up))
		{
			position.y -= dt * speed;
		}
		else if (InputMgr::GetKey(Keyboard::Down))
		{
			position.y += dt * speed;
		}
	}
}

/*============================================
		디자인 패턴 : 유한 상태 머신
==============================================*/
void Player::UpdateAnimation(float dt)
{
	switch (moveMent)
	{
	case PlayerAction::IDLE: //가만히 있을 때
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			isRight = true;
			SetAnimation(PlayerAction::MOVE);
		}
		else if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			isRight = false;
			SetAnimation(PlayerAction::MOVE);
		}
		else if (InputMgr::GetKey(Keyboard::Right) || InputMgr::GetKey(Keyboard::Left))
		{
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Up))
		{
			SetAnimation(PlayerAction::LOOKUP);
		}
		if (InputMgr::GetKey(Keyboard::Down))
		{
			SetAnimation(PlayerAction::LOOKDOWN);
		}
		if (InputMgr::GetKey(Keyboard::C))
		{
			SetAnimation(PlayerAction::JUMP);
		}
		if (InputMgr::GetKeyDown(Keyboard::X))
		{
			SetAnimation(PlayerAction::DASH);
		}
		//if (InputMgr::GetKey(Keyboard::Z))
		//{
		//	if (isCollision[2] || isCollision[3])
		//	{
		//		SetAnimation(PlayerAction::CLIMB);
		//	}			
		//}
		break;
	case PlayerAction::MOVE: //Right or Left
		if (InputMgr::GetKeyUp(Keyboard::Right) || InputMgr::GetKeyUp(Keyboard::Left))
		{
			SetAnimation(PlayerAction::IDLE);
		}
		if (InputMgr::GetKey(Keyboard::Up))
		{
			SetAnimation(PlayerAction::LOOKUP);
		}
		if (InputMgr::GetKey(Keyboard::Down))
		{
			SetAnimation(PlayerAction::LOOKDOWN);
		}
		if (InputMgr::GetKeyDown(Keyboard::C))
		{
			SetAnimation(PlayerAction::JUMP);
		}
		if (InputMgr::GetKeyDown(Keyboard::X))
		{
			SetAnimation(PlayerAction::DASH);
		}
		if (InputMgr::GetKey(Keyboard::Z))
		{
			if (isCollision[2] || isCollision[3])
			{
				SetAnimation(PlayerAction::CLIMB);
			}
		}
		break;

	case PlayerAction::JUMP:
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			isRight = true;
			SetAnimation(PlayerAction::MOVE);
		}
		else if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			isRight = false;
			SetAnimation(PlayerAction::MOVE);
		}
		else if (InputMgr::GetKey(Keyboard::Right) || InputMgr::GetKey(Keyboard::Left))
		{
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Up))
		{
			SetAnimation(PlayerAction::LOOKUP);
		}
		if (InputMgr::GetKey(Keyboard::Down))
		{
			SetAnimation(PlayerAction::LOOKDOWN);
		}
		if (InputMgr::GetKeyDown(Keyboard::X))
		{
			SetAnimation(PlayerAction::DASH);
		}
		if (InputMgr::GetKey(Keyboard::Z))
		{
			if (isCollision[2] || isCollision[3])
			{
				SetAnimation(PlayerAction::CLIMB);
			}
		}
		break;

	case PlayerAction::DASH:
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			isRight = true;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			isRight = false;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Right) || InputMgr::GetKey(Keyboard::Left))
		{
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Up))
		{
			SetAnimation(PlayerAction::LOOKUP);
		}
		if (InputMgr::GetKey(Keyboard::Down))
		{
			SetAnimation(PlayerAction::LOOKDOWN);
		}
		if (InputMgr::GetKeyDown(Keyboard::C))
		{
			SetAnimation(PlayerAction::JUMP);
		}
		if (InputMgr::GetKey(Keyboard::Z))
		{
			if (isCollision[2] || isCollision[3])
			{
				SetAnimation(PlayerAction::CLIMB);
			}
		}
		break;

	case PlayerAction::LOOKUP:
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			isRight = true;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			isRight = false;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Right) || InputMgr::GetKey(Keyboard::Left))
		{
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKeyUp(Keyboard::Up))
		{
			SetAnimation(PlayerAction::IDLE);
		}
		if (InputMgr::GetKey(Keyboard::Down))
		{
			SetAnimation(PlayerAction::LOOKDOWN);
		}
		if (InputMgr::GetKeyDown(Keyboard::C))
		{
			SetAnimation(PlayerAction::JUMP);
		}
		if (InputMgr::GetKeyDown(Keyboard::X))
		{
			SetAnimation(PlayerAction::DASH);
		}
		if (InputMgr::GetKey(Keyboard::Z))
		{
			if (isCollision[2] || isCollision[3])
			{
				SetAnimation(PlayerAction::CLIMB);
			}
		}
		break;

	case PlayerAction::LOOKDOWN:
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			isRight = true;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			isRight = false;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Right) || InputMgr::GetKey(Keyboard::Left))
		{
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Up))
		{
			SetAnimation(PlayerAction::LOOKUP);
		}
		if (InputMgr::GetKeyUp(Keyboard::Down))
		{
			SetAnimation(PlayerAction::IDLE);
		}
		if (InputMgr::GetKey(Keyboard::C))
		{
			SetAnimation(PlayerAction::JUMP);
		}
		if (InputMgr::GetKeyDown(Keyboard::X))
		{
			SetAnimation(PlayerAction::DASH);
		}
		if (InputMgr::GetKey(Keyboard::Z))
		{
			if (isCollision[2] || isCollision[3])
			{
				SetAnimation(PlayerAction::CLIMB);
			}
		}
		break;

	case PlayerAction::CLIMB:
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			isRight = true;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			isRight = false;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Right) || InputMgr::GetKey(Keyboard::Left))
		{
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Up))
		{
			SetAnimation(PlayerAction::CLIMB);
			//isSeizeWall = true;
		}
		if (InputMgr::GetKey(Keyboard::Down))
		{
			SetAnimation(PlayerAction::CLIMB);
			//isSeizeWall = false;
			//SetAnimation(PlayerAction::LOOKDOWN);
		}
		if (InputMgr::GetKey(Keyboard::C))
		{
			SetAnimation(PlayerAction::JUMP);
		}
		if (InputMgr::GetKeyUp(Keyboard::Z))
		{
			SetAnimation(PlayerAction::IDLE);
		}
		break;

	default:
		break;
	}
}
/*========================================
	행위에 따른 플레이어의 애니메이션
==========================================*/
void Player::SetAnimation(PlayerAction action)
{
	PlayerAction pastAction = moveMent;
	moveMent = action;

	switch (moveMent)
	{
	case PlayerAction::IDLE:
		if (isRight == true)
		{
			sprite.setScale(CharacSize, CharacSize);
			animation.Play("Idle");
		}
		else if (isRight == false)
		{
			sprite.setScale(-CharacSize, CharacSize);
			animation.Play("Idle");
		}
		break;
	case PlayerAction::MOVE:
		if (isRight == true)
		{
			animation.Play("Move");
			sprite.setScale(CharacSize, CharacSize);
		}
		else if (isRight == false)
		{
			animation.Play("Move");
			sprite.setScale(-CharacSize, CharacSize);
		}
		break;
	case PlayerAction::JUMP:
		isJump = true;
		animation.Play("Jump");
		//animation.PlayQueue("Idle");
		break;
	case PlayerAction::DASH:
		isDash = true;
		//animation.Play("");
		animation.PlayQueue("Idle");
		break;
	case PlayerAction::LOOKUP:
		if (isSeizeWall == false)
		{
			animation.Play("Lookup");
		}
		break;
	case PlayerAction::LOOKDOWN:
		if (isRight == true)
		{
			sprite.setScale(CharacSize, CharacSize - 0.5f);
		}
		else if (isRight == false)
		{
			sprite.setScale(-CharacSize, CharacSize - 0.5f);
		}
		break;
	case PlayerAction::CLIMB:
		if (isCollision[2] || isCollision[3])
		{
			isSeizeWall = true;
		}
		animation.PlayQueue("Climb");
		break;
	default:
		break;
	}
}

FloatRect Player::GetGobalBound() const
{
	return sprite.getGlobalBounds();
}

FloatRect Player::BodyHitGetGobalBound() const
{
	return bodyHitbox.getGlobalBounds();
}

FloatRect Player::FloorHitGetGoalBound() const
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
	   애니메이션 CSV설정
================================*/

void Player::AnimationInit()
{
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