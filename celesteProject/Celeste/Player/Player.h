#pragma once
#include "../Utils/AnimationController.h"
#include <vector>
#include <list>
#include "../Wall.h"
#include "../Bat.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 300; // 시작 플레이어 속도
	const float GRAVITY = 980.f; // 중력 처리

	Sprite sprite; //플레이어 그리기
	Vector2f position; // 플레이어의 위치
	
	AnimationController animation; 
	Vector2i resolution;

	Texture texture;
	std::map<std::string, Texture> texMap;

	bool isJump; // 플레이어 점프 유무
	bool isDash; // 플레이어 대쉬 유무	
	bool isCatch; //플레이어 잡기 유무
	bool isFalling; //플레이어 중력 유무

	float gravity;
	float gravityV;

	IntRect arena;

	Vector2f direction;
	float speed;
	float timer;	

public:
	Player();

	void Init();

	void Spawn(IntRect arena, Vector2i res);
	
	void UpdateInput();
	void Update(float dt, std::vector<Wall*> walls);

	FloatRect GetGobalBound() const;

	Vector2f GetPosition() const;

	Sprite GetSprite() const;

	void Draw(RenderWindow &window);

	


};

