#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../SceneMgr/SceneMgr.h"


using namespace sf;
using namespace std;

class TItle : public Scene
{
private:


	String backGrndTexture;
	String logoTexture;
	string cTexture;

	Sprite backGrnd;
	Sprite logoSprite;
	Sprite cSprite;

	FloatRect titleRect;
	Vector2f titleCenter;

	SceneID currScene;

public:
	
	TItle();
	virtual void Init(Vector2i resolution);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();


};

