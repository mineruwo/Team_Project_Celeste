#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../SceneMgr/SceneMgr.h"
#include "../Utils/UiMgr.h"
#include "../Utils/GameInfoMgr.h"
#include "../SceneMgr/SelectMapSpriteMgr.h"
#include "Snow.h"

using namespace sf;
using namespace std;

class ConfirmSelectedMapScene : public Scene
{
private:
	Snow snow;

	bool firstMapOnOff;
	
	bool tutorial = true;
	bool first = false;


	SceneID currScene;

public:
	ConfirmSelectedMapScene();
	void GetTutorialClear();
	virtual void Init(Vector2i resolution);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();

};

