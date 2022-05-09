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
	const float START_SPEED = 300; // ���� �÷��̾� �ӵ�
	const float GRAVITY = 980.f; // �߷� ó��
	const float CharacSize = 4.f;
	const int START_DASH = 1;

	PlayerAction action = PlayerAction::IDLE;

	Sprite sprite; //�÷��̾� �׸���
	Vector2f position; // �÷��̾��� ��ġ
	Vector2f prePosition; //�÷��̾��� ���� ��ġ
	
	AnimationController animation; 
	Vector2i resolution;

	Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f deshDir;
	int dashCount;

	float jumpspeed;

	bool isFloor; //�÷��̾� �ٴ� ����
	bool isRight; //�÷��̾� ������ ����
	bool isJump; // �÷��̾� ���� ����
	bool isDash; // �÷��̾� �뽬 ����	
	bool isCatch; //�÷��̾� ��� ����
	bool isFalling; //�÷��̾� �߷� ����
	bool isSeizeWall; //�÷��̾� ���� ������ ��


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

