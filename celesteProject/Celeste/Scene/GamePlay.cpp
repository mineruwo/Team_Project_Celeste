#include "GamePlay.h"

GamePlay::GamePlay():currScene(SceneID::GamePlay)
{
	
}


void GamePlay::CreateWalls(std::vector<Wall*>& walls, Map& mapdata)
{
	for (auto v : walls)
	{
		delete v;
	}

	walls.clear();

	int idx = 0;

	while (true)
	{

		if (idx == mapdata.Getblocks().size())
		{
			break;
		}

		Wall* tile = new Wall(mapdata.Getblocks()[idx]->getGlobalBounds(), idx);
		walls.push_back(tile);

		idx++;

	}

}

void GamePlay::Init(Vector2i resolution)
{
	map.LoadMap();
	CreateWalls(walls, map);
	player.Init();

	currScene = SceneID::GamePlay;
}

void GamePlay::Update(Time dt, RenderWindow& window)
{
	map.InputMap(windowMagnification, mainView, dt, window);
	if (dt.asSeconds() <= 1.f / 200.f)
	{
		InputMgr::Update(dt.asSeconds());
		player.Update(dt.asSeconds(), walls);
	}	

	if (InputMgr::GetKeyDown(Keyboard::F2))
	{
		player.Init();
	}
}

void GamePlay::Draw(RenderWindow& window)
{
	window.setView(mainView);
	player.Draw(window);
	
	for (auto it : walls)
	{
		it->DrawWall(window);
	}

	for (auto it : map.GetObjs())
	{
		window.draw(it->GetSprite());
	}
}

void GamePlay::Release()
{
}
