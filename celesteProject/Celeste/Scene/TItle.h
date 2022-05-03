#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"

using namespace sf;
using namespace std;

class TItle : public Scene
{
private:
	Texture temp;

	String backGrndName;
	String logoName;
	string cName;

	Sprite backGrnd;
	Sprite logoSprite;
	Sprite cSprite;

	FloatRect titleRect;

	SceneID currScene;

public:
	virtual void Init(Vector2i resolution);
	virtual void Update();
	virtual void Draw(RenderWindow& window);
	virtual void Release();


};

