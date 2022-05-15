#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../SceneMgr/SceneMgr.h"
#include "../Wall.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Object/Berry.h"
#include "../Object/Thorny.h"

using namespace sf;
using namespace std;

class GamePlay : public Scene
{
private:

	Player player;
	bool isPlayerInit = false;
	View mainView;
	View backView;
	int windowMagnification = 2;
	bool initBackView = false;
	Sprite backGround;
	Berry berry;
	Thorny thorny;

	Map map;
	std::vector <Wall*> walls;
	IntRect area;
	SceneID currScene;

public:

	GamePlay();

	void CreateWalls(std::vector<Wall*>& walls, Map& mapdata);

	virtual void Init(Vector2i resolution);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(RenderWindow& window);
	virtual void Release();

};

