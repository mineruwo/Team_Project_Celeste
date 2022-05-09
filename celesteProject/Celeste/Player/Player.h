#pragma once
#include "../Utils/AnimationController.h"
#include <vector>
#include <list>
#include "../Wall.h"
#include "../Bat.h"
#include "../Bat2.h"
#include <SFML/Graphics.hpp>

using namespace sf;

enum class PlayerAction
{
	IDLE,
	MOVE,
	JUMP,
	DASH,
};


class Player
{
private:
	const float START_SPEED = 300; // 시작 플레이어 속도
	const float GRAVITY = 980.f; // 중력 처리
	const float CharacSize = 4.f;
	const int START_DASH = 1;

	PlayerAction action = PlayerAction::IDLE;

	Sprite sprite; //플레이어 그리기
	Vector2f position; // 플레이어의 위치
	Vector2f prePosition; //플레이어의 이전 위치
	
	AnimationController animation; 
	Vector2i resolution;

	Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f deshDir;
	int dashCount;

	float jumpspeed;

	bool isFloor; //플레이어 바닥 유무
	bool isRight; //플레이어 오른쪽 유무
	bool isJump; // 플레이어 점프 유무
	bool isDash; // 플레이어 대쉬 유무	
	bool isCatch; //플레이어 잡기 유무
	bool isFalling; //플레이어 중력 유무
	bool isSeizeWall; //플레이어 벽을 붙잡을 때


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

	float gravity;
	float gravityV;

	float speed;
	float timer;	

	bool isCollision[4]; // Up Down Left Right
public:
	Player();

	void Init();

	//void Spawn(IntRect arena, Vector2i res);
	
	void Crash(std::vector<Wall *> walls);

	void UpdateInput();
	void Update(float dt, std::vector<Wall*> walls);

	FloatRect GetFloorGobalBound() const;

	Vector2f GetPosition() const;

	Sprite GetSprite() const;

	void Draw(RenderWindow &window);

	


};

