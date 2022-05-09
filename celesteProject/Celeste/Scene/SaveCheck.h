#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../SceneMgr/SceneMgr.h"
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

	Sprite backGrnd;
	Sprite characterCard[3];
	Sprite characterTicket[3];
	Sprite cSprite;
	Sprite xSprite;

	float cardCenter;
	float ticketCenter;

	SceneID currScene;

public:
	SaveCheck();
	virtual void Init(Vector2i resolution);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();


};

