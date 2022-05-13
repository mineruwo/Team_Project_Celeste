#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../SceneMgr/SceneMgr.h"
#include "../Utils/UiMgr.h"
#include "Snow.h"

using namespace sf;
using namespace std;

class ConfirmSelectedMapScene : public Scene
{
private:
	Snow snow;

	SceneID currScene;
	
	




public:
	ConfirmSelectedMapScene();
	virtual void Init(Vector2i resolution);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();

};

