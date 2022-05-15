#pragma once
#include "../Utils/AnimationController.h"
#include <vector>
#include <list>
#include "../Wall.h"
#include "PlayerHair.h"
#include <SFML/Graphics.hpp>

using namespace sf;

enum class PlayerAction
{
	IDLE,
	MOVE,
	JUMP,
	DASH,
	LOOKUP,
	LOOKDOWN,
	CLIMB
};

enum class PlayerDir // �÷��̾� Ű
{
	R, L, U, D,
	RU, LU, RD, LD
};


class Player
{
private:
	const float START_SPEED = 200; // ���� �÷��̾� �ӵ�
	const float START_JUMPSPEED = 400.f;
	const float GRAVITY = 400.f; // �߷� ó��
	const float CharacSize = 2.f;

	AnimationController animation;

	PlayerAction moveMent = PlayerAction::IDLE;
	PlayerDir keyDir;

	Sprite sprite; //�÷��̾� �׸���
	Vector2f position; // �÷��̾��� ��ġ
	Vector2f prePosition; //�÷��̾��� ���� ��ġ
	//float nowPosition; //�÷��̾��� �̵�[�밢��]

	Vector2i resolution;

	Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f deshDir;

	float jumpspeed;
	float jumpTime;
	float statusDT; //dt ����

	bool isUp;
	bool isFloor; //�÷��̾� �ٴ� ����
	bool isRight; //�÷��̾� ������ ����
	bool isJump; // �÷��̾� ���� ����
	bool isDash; // �÷��̾� �뽬 ����	
	bool isCatch; //�÷��̾� ��� ����
	bool isFalling; //�÷��̾� �߷� ����
	bool isSeizeWall; //�÷��̾� ���� ������ ��

	float jumpSpeed;
	float fallingAcc;

	float gravity;
	float gravityV;

	float speed;
	float timer;

	bool isCollision[4]; // 0.Right 1.Left 2.Top 3.Bottom 

	/*====================
		  ĳ���� �Ӹ�
	======================*/	
	RectangleShape hair;
	Vector2f hairPosition;
	/*====================
	   ĳ���� �� ��Ʈ�ڽ�
	======================*/
	RectangleShape bodyHitbox;
	Vector2f bodyPosition;
	/*=====================
		ĳ���� �ٴ� ��Ʈ�ڽ�
	=======================*/
	RectangleShape floorHitbox;
	Vector2f floorPosition;

public:
	Player();

	void Init();

	//void Spawn(IntRect arena, Vector2i res);

	void UpdateCrash(std::vector<Wall*> walls);

	void Update(float dt, std::vector<Wall*> walls);

	void Jump(float dt);
	void Move(float dt);
	void Dash(float dt);
	void Climb(float dt);

	void UpdateAnimation(float dt);
	void SetAnimation(PlayerAction action);

	FloatRect GetGobalBound() const;
	FloatRect BodyHitGetGobalBound() const;
	FloatRect FloorHitGetGoalBound() const;

	Vector2f GetPosition() const;

	Sprite GetSprite() const;


	void AnimationInit();
	void Draw(RenderWindow& window);

	// add for obj //
	void ResetPosition();
	Vector2f GetPrePosition();
	//----------------------------//


};

