#pragma once
#include "Scene.h"
#include "../SceneMgr/SceneMgr.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"

using namespace sf;
using namespace std;

class MainMenu : public Scene
{
private:

	String menuBackGrndTexture;
	String climbTexture;
	String optionTexture;
	String creditTexture;
	String exitTexture;
	string cTexture;
	string xTexture;

	Sprite menuBackGrnd;
	Sprite climn;
	Sprite option;
	Sprite credit;
	Sprite exit;
	Sprite cSprite;
	Sprite xSprite;

	int menuNum = 0;

	SceneID currScene;

public:
	MainMenu();
	virtual void Init(Vector2i resolution);
	virtual void SelctClimn(Time dt);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();


};

