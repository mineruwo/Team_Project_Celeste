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
	const float START_SPEED = 200; // 시작 플레이어 속도
	const float START_JUMPSPEED = 800.f;
	const float GRAVITY = 200.f; // 중력 처리
	const float CharacSize = 2.f;

	AnimationController animation;

	PlayerAction moveMent = PlayerAction::IDLE;

	Sprite sprite; //플레이어 그리기
	Vector2f position; // 플레이어의 위치
	Vector2f prePosition; //플레이어의 이전 위치
	
	Vector2i resolution;

	Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f deshDir;

	float jumpspeed;
	float jumpTime;
	float statusDT; //dt 변수

	bool isFloor; //플레이어 바닥 유무
	bool isRight; //플레이어 오른쪽 유무
	bool isUp;
	bool isJump; // 플레이어 점프 유무
	bool isDash; // 플레이어 대쉬 유무	
	bool isCatch; //플레이어 잡기 유무
	bool isFalling; //플레이어 중력 유무
	bool isSeizeWall; //플레이어 벽을 붙잡을 때

	float jumpSpeed;
	float fallingSpeed;

	float gravity;
	float gravityV;

	float speed;
	float timer;

	bool isCollision[4]; // 0.Right 1.Left 2.Top 3.Bottom 

	/*====================
	   캐릭터 몸 히트박스
	======================*/
	RectangleShape bodyHitbox;
	Vector2f bodyPosition;
	/*=====================
		캐릭터 바닥 히트박스
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

