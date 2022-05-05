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
	const float START_SPEED = 300; // ���� �÷��̾� �ӵ�
	const float GRAVITY = 980.f; // �߷� ó��

	Sprite sprite; //�÷��̾� �׸���
	Vector2f position; // �÷��̾��� ��ġ
	
	AnimationController animation; 
	Vector2i resolution;

	Texture texture;
	std::map<std::string, Texture> texMap;

	bool isJump; // �÷��̾� ���� ����
	bool isDash; // �÷��̾� �뽬 ����	
	bool isCatch; //�÷��̾� ��� ����
	bool isFalling; //�÷��̾� �߷� ����

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

