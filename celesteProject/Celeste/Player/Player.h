#pragma once
#pragma warning(disable : 4996)
#include "../Utils/AnimationController.h"
#include <vector>
#include <list>
#include "../Wall.h"
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


class Player
{
private:
	const float START_SPEED = 200; // ���� �÷��̾� �ӵ�
	const float START_JUMPSPEED = 800.f;
	const float GRAVITY = 200.f; // �߷� ó��
	const float CharacSize = 2.f;

	AnimationController animation;

	PlayerAction moveMent = PlayerAction::IDLE;

	Sprite sprite; //�÷��̾� �׸���
	Vector2f position; // �÷��̾��� ��ġ
	Vector2f prePosition; //�÷��̾��� ���� ��ġ
	
	Vector2i resolution;

	Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f deshDir;

	float jumpspeed;
	float jumpTime;
	float statusDT; //dt ����

	bool isFloor; //�÷��̾� �ٴ� ����
	bool isRight; //�÷��̾� ������ ����
	bool isUp;
	bool isJump; // �÷��̾� ���� ����
	bool isDash; // �÷��̾� �뽬 ����	
	bool isCatch; //�÷��̾� ��� ����
	bool isFalling; //�÷��̾� �߷� ����
	bool isSeizeWall; //�÷��̾� ���� ������ ��

	float jumpSpeed;
	float fallingSpeed;

	float gravity;
	float gravityV;

	float speed;
	float timer;

	bool isCollision[4]; // 0.Right 1.Left 2.Top 3.Bottom 

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

	Font font;
	Text poscheck;

public:
	Player();

	void Init();

	//void Spawn(IntRect arena, Vector2i res);

	void UpdateCrash(std::vector<Wall*> walls);

	void Update(float dt, std::vector<Wall *> walls);

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




};

