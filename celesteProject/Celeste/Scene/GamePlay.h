#pragma once
#include "Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../SceneMgr/SceneMgr.h"
#include "../Wall.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

using namespace sf;
using namespace std;

class GamePlay : public Scene
{
private:

	Player player;
	bool isPlayerInit = false;
	View mainView;
	int windowMagnification = 2;

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

