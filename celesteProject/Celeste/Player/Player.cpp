#include "Player.h"
#include "../Utils/InputMgr.h"
#include "../Utils/Utils.h"
#include "../Utils/repidcw.h"
#include <math.h>
#include <iostream>

/*==============================
		 �÷��̾� ������
================================*/
Player::Player()
	:speed(START_SPEED), isJump(false), isDash(false), isCatch(false)
	, isFalling(true), isSeizeWall(false), isRight(true), isFloor(false),
	jumpTime(0.f), jumpSpeed(START_JUMPSPEED), fallingAcc(0.f)
{
}
  
/*==============================
		 �÷��̾� �ʱ�ȭ
================================*/
void Player::Init()
{
	position.x = 815.f;
	position.y = 511.f;
	sprite.setPosition(position); //815, 511
	sprite.setScale(CharacSize, CharacSize);
	sprite.setOrigin(Vector2f((16.f * CharacSize)*0.5f, 32.f * CharacSize));

	//�� ��Ʈ �ڽ�
	bodyHitbox.setFillColor(Color::Transparent);
	bodyHitbox.setOutlineColor(Color::Yellow);
	bodyHitbox.setOutlineThickness(1.f);
	bodyHitbox.setSize(Vector2f(8.f * CharacSize, 10.f * CharacSize));
	bodyHitbox.setOrigin(Vector2f((8.f * CharacSize) * 0.5f, 10.f * CharacSize));	
	//bodyHitbox.setPosition(position);

	//�ٴ� ��Ʈ �ڽ�
	floorHitbox.setFillColor(Color::Red);
	floorHitbox.setSize(Vector2f(8.f * CharacSize, 2.f * CharacSize));
	floorHitbox.setOrigin(Vector2f((8.f * CharacSize)*0.5f, 2.f * CharacSize));

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
	Ű �Է¿� ���� �÷��̾��� �׼� ������Ʈ
==============================================*/
void Player::Update(float dt, std::vector<Wall *> walls)
{
	isFalling = moveMent != PlayerAction::DASH && !isFloor && moveMent != PlayerAction::CLIMB;

	// �� ��
	if (isFalling)
	{
		std::cout << gravityV << std::endl;
		if (gravityV > 980.f) //�ִ� �߷� ����
		{
			gravityV = 980.f;
		}
		gravityV += GRAVITY * dt;
		position.y += gravityV * dt;

		sprite.setPosition(position);
		bodyHitbox.setPosition(position);
	}
	else
	{
		gravityV = 0.f;
	}

	//�浹 ó�� ������Ʈ
	UpdateCrash(walls);	

	//std::cout << (int)moveMent << std::endl;
	Move(dt);
	if (isJump)
	{
		Jump(dt);
	}

	if (moveMent == PlayerAction::DASH)
	{
		Dash(dt);
	}
	if (moveMent == PlayerAction::CLIMB)
	{
		Climb(dt);
	}

	statusDT = dt;

	animation.Update(dt);
	UpdateAnimation(dt);

	
	sprite.setPosition(position);
	bodyHitbox.setPosition(position);
	floorHitbox.setPosition(position);
}

/*========================================
				�浹 ó��
==========================================*/
void Player::UpdateCrash(std::vector<Wall*> walls)
{
	for (auto& c : isCollision)
	{
		c = false;
	}
	isFloor = false;
	isSeizeWall = false;
	for (auto v : walls)
	{
		// �÷��̾��� origin�� �̿�
		// x > y �ϰ�� (��/�Ʒ�)���� ����, x < y�� ��� (������/����)���� ����
		
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

			float playerX = bodyHitbox.getPosition().x;
			float playerY = bodyHitbox.getPosition().y - bodyHitbox.getGlobalBounds().height * 0.5;
			Vector2f posi = bodyHitbox.getPosition();

			//LT
			if (wallLeft > playerX && wallTop > playerY)
			{
				isFloor = true;
				//X�� ū ���� �� ��� ���� ����
				if (abs(wallTop - playerBottom) < abs(wallLeft - playerRight))
				{
					//std::cout << v->GetId() << "LTX�浹" << std::endl;
					//posi.y = wallTop + 2.f;
					posi.y = wallTop + 1.f;
					//gravityV = 0.f;
				}
				//Y�� ū ���� �� ��� ������ ����
				else if (abs(wallTop - playerBottom) > abs(wallLeft - playerRight))
				{
					//std::cout << v->GetId() << "LTY�浹" << std::endl;
					posi.x = wallLeft - bodyHitbox.getGlobalBounds().width * 0.5;
				}
				//X�� Y ���� ������ ���
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
				std::cout << v->GetId() << "CT�浹" << std::endl;
				posi.y = wallTop + 1.f;
				//gravityV = 0.f;
			}
			//RT
			if (wallRight < playerX && wallTop > playerY)
			{
				isFloor = true;

				//std::cout << v->GetId() << "RT�浹" << std::endl;
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
				isCollision[1] = true;
				isSeizeWall = true;
				//std::cout << v->GetId() << "LC�浹" << std::endl;
				posi.x = wallLeft - bodyHitbox.getGlobalBounds().width * 0.5f + 1.f;
			}
			//RC
			if (wallRight < playerX && wallTop < playerY && wallBottom > playerY)
			{
				isCollision[0] = true;
				isSeizeWall = true;
				//std::cout << "RC�浹" << std::endl;
				posi.x = wallRight+bodyHitbox.getGlobalBounds().width * 0.5f - 1.f;
			}
			//LB
			if (wallBottom < playerY && wallLeft > playerX)
			{
				//std::cout << v->GetId() << "LB�浹" << std::endl;
				//X
				if (abs(wallBottom - playerTop) < abs(wallLeft - playerRight))
				{
					posi.y = wallBottom + bodyHitbox.getGlobalBounds().height;
				}
				//Y
				else if (abs(wallBottom - playerTop) > abs(wallLeft - playerRight))
				{
					posi.x = wallLeft - bodyHitbox.getGlobalBounds().width*0.5f;
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
				//std::cout << v->GetId() << "CB�浹" << std::endl;
				posi.y = wallBottom + bodyHitbox.getGlobalBounds().height;
			}
			//RB
			if (wallBottom < playerY && wallRight < playerX)
			{
				//std::cout << v->GetId() << "RB�浹" << std::endl;
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
		���� �׼� �ڵ�
=============================*/
void Player::Jump(float dt)
{
	//isFalling = false;
	//if (isJump == true)
	//{
	//	jumpSpeed -= GRAVITY * dt;
	//	position.y -= jumpSpeed * dt;
	//	if (jumpSpeed < 0.f)
	//	{
	//		isJump = false;
	//		jumpSpeed = START_JUMPSPEED;
	//	}
	//}
	//else if (isJump == false)
	//{
	//	fallingAcc += GRAVITY * dt;
	//	if (fallingAcc > 1000.f)
	//	{
	//		fallingAcc = 1000.f;
	//	}
	//}
	/*if (InputMgr::GetKeyDown(Keyboard::C))
	{

	}*/
	/*if (InputMgr::GetKeyUp(Keyboard::C))
	{
		jumpTime = 0.5f;
	}
	if (InputMgr::GetKey(Keyboard::C))
	{
		jumpTime += dt;
		if (jumpTime < 0.5f)
		{
			gravity -= GRAVITY * dt;
		}
	}*/
}

/*===========================
	  �����̴� �׼� �ڵ�
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
	  �����̴� �뽬 �ڵ�
=============================*/
void Player::Dash(float dt)
{	
	if (isDash = true)
	{
		if (isRight == true)
		{
			if (position.x < deshDir.x + 150.f)
			{
				position.x += dt * speed * 2.f;
			}
			else
			{
				isFalling = true;
				isDash = false;
			}	
			
		}
		else if (isRight == false)
		{
			if (position.x > deshDir.x - 150.f)
			{
				position.x -= dt * speed * 2.f;
			}
			else
			{
				isFalling = true;
				isDash = false;
			}
		}
		if (position.x < deshDir.x + 150.f || position.x > deshDir.x - 150.f)
		{
			
			gravityV = 0.f;
			isDash = false;
		}
	}
	else if (isDash == false)
	{
		moveMent = PlayerAction::IDLE;
		
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
	  ��Ÿ�� �׼� �ڵ�
=============================*/
void Player::Climb(float dt)
{
	if (isCollision[0] || isCollision[1])
	{
		if (InputMgr::GetKey(Keyboard::Up))
		{
			position.y -= dt * speed;
		}
		else if (InputMgr::GetKey(Keyboard::Down))
		{
			position.y += dt * speed;
		}
		std::cout << "Climb: " << position.y << std::endl;
	}	
}

/*============================================
		������ ���� : ���� ���� �ӽ�
==============================================*/
void Player::UpdateAnimation(float dt)
{
	switch (moveMent)
	{
	case PlayerAction::IDLE: //������ ���� ��
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
		if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			isRight = false;
			SetAnimation(PlayerAction::MOVE);
		}
		if (InputMgr::GetKey(Keyboard::Right) || InputMgr::GetKey(Keyboard::Left))
		{
			SetAnimation(PlayerAction::MOVE);
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
		if  (InputMgr::GetKeyDown(Keyboard::Left))
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
	������ ���� �÷��̾��� �ִϸ��̼�
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
		isFloor = false;
		animation.Play("Jump");
		gravityV -= 230;
		//animation.PlayQueue("Idle");
		break;
	case PlayerAction::DASH:
		isDash = true;
		deshDir = position;
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
		animation.Play("Climb");
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

void Player::UpdateKeybord()
{
	switch (keyDir)
	{
	case PlayerDir::R:
		InputMgr::GetKey(Keyboard::Right);
		break;
	case PlayerDir::L:
		InputMgr::GetKey(Keyboard::Left);
		break;
	case PlayerDir::U:
		InputMgr::GetKey(Keyboard::Up);
		break;
	case PlayerDir::D:
		InputMgr::GetKey(Keyboard::Down);
		break;
	case PlayerDir::RU:
		InputMgr::GetKey(Keyboard::Right)&& InputMgr::GetKey(Keyboard::Up);
		break;
	case PlayerDir::LU:
		InputMgr::GetKey(Keyboard::Left) && InputMgr::GetKey(Keyboard::Up);
		break;
	case PlayerDir::RD:
		InputMgr::GetKey(Keyboard::Right) && InputMgr::GetKey(Keyboard::Down);
		break;
	case PlayerDir::LD:
		InputMgr::GetKey(Keyboard::Left) && InputMgr::GetKey(Keyboard::Down);
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
	   �ִϸ��̼� CSV����
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
		�÷��̾� �׸���
================================*/
void Player::Draw(RenderWindow& window)
{
	
	window.draw(floorHitbox);
	window.draw(bodyHitbox);	
	window.draw(sprite);
}
void Player::ResetPosition()
{
	sprite.setPosition(Vector2f(815.f,511.f));
	bodyHitbox.setPosition(Vector2f(815.f, 511.f));
	floorHitbox.setPosition(Vector2f(815.f, 511.f));
	position = Vector2f(815.f, 511.f);

}

Vector2f Player::GetPrePosition()
{
	return position;
}

/*===============================
�� �� �� : �� �� ȭ
�� �� �� �� : �÷��̾� ���� ����
�� �� �� : 2022 - 05 - 04
�� �� �� : 2022 - 05 - 06
 - �浹ó�� ����
 - ���� Ű ����
 - �뽬 Ű ����
=================================*/