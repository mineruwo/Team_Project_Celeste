#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../SceneMgr/SceneMgr.h"
#include"../Utils/GameInfoMgr.h"
#include "../Scene/ConfirmSelectedMapScene.h"
#include "Snow.h"

using namespace sf;
using namespace std;

class SaveCheck : public Scene
{
private:

	Snow snow;

	String backGrndTexture;
	String characterCardTexture;
	String characterTicketTexture;
	string cTexture;
	string xTexture;
	string berryTexture;
	string deathTexture;

	Sprite backGrnd;
	Sprite characterCard[3];
	Sprite characterTicket[3];
	Sprite cSprite;
	Sprite xSprite;
	Sprite berrySprite[3];
	Sprite deathSprite[3];


	String faceTexture;
	Sprite face[3];


	bool isMove = false;
	bool isRollback = true;

	float cardCenter;
	float ticketCenter;

	float MoveX;
	float RollX;
	int selectLoad = 0;
	// save index 번호 가질변수 > 맵선택에 클리어여부 전달 
	int Index;
	SceneID currScene;

public:
	SaveCheck();	


	virtual void Init(Vector2i resolution);
	void moveCard(int select);
	//void MoveCard(int select, Time dt);
	//void RollBackCard(int select, Time dt);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();


};

