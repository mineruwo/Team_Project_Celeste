#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"

using namespace sf;
using namespace std;

class MainMenu : public Scene
{
private:

	String menuBackGrndTexture;
	String ClimbTexture;
	String optionTexture;
	String CreditTexture;
	String exitTexture;
	string cTexture;
	string xTexture;

	Sprite menuBackGrnd;
	Sprite Climn;
	Sprite option;
	Sprite credit;
	Sprite exit;
	Sprite cSprite;
	Sprite xSprite;

	SceneID currScene;

public:
	MainMenu();
	virtual void Init(Vector2i resolution);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();


};

