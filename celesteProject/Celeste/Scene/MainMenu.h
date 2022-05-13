#pragma once
#include "Scene.h"
#include "../SceneMgr/SceneMgr.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "Snow.h"
#include "../Utils/UiMgr.h"

using namespace sf;
using namespace std;

class MainMenu : public Scene
{
private:

	Snow snow;
	String menuBackGrndTexture;
	String climbTexture;
	String optionTexture;
	String creditTexture;
	String exitTexture;
	string cTexture;
	string xTexture;

	Sprite menuBackGrnd;
	Sprite climb;
	Sprite option;
	Sprite credit;
	Sprite exit;
	Sprite cSprite;
	Sprite xSprite;

	int menuNum = 0;
	bool climbBounce ;
	bool climbUp = true;
	bool isOption = false;
	bool isCredit = false;

	SceneID currScene;
	

public:
	MainMenu();
	virtual void Init(Vector2i resolution);
	virtual void SelectClimb(Time dt);
	virtual void SelectOption();
	virtual void Selectcredit();
	virtual void Selectexit();

	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();


};

