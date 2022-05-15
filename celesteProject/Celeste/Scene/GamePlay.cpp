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

		Wall* tile = new Wall(mapdata.Getblocks()[idx]->getGlobalBounds());
		walls.push_back(tile);

		idx++;

	}


}

void GamePlay::Init(Vector2i resolution)
{
	map.LoadMap();
	CreateWalls(walls, map);
	mainView.reset(FloatRect(0, 0, area.width / windowMagnification, area.height / windowMagnification));
	backGround.setTexture(TextureHolder::GetTexture("graphics/Background.png"));
	backGround.setScale(Vector2f(2.0f, 2.0f));

	berry.Init();
	thorny.Init();
	player.Init();

	currScene = SceneID::GamePlay;
}

void GamePlay::Update(Time dt, RenderWindow& window)
{
	map.InputMap(windowMagnification, mainView, dt);
	//if (dt.asSeconds() <= 1.f / 200.f)
	//{
	//	InputMgr::Update(dt.asSeconds());
	//	player.Update(dt.asSeconds(), walls);
	//}	

	player.Update(dt.asSeconds(), walls);
	mainView.setCenter(player.GetPosition().x, player.GetPosition().y);
	berry.Update(player, dt.asSeconds());
	thorny.Update(player);
}

void GamePlay::Draw(RenderWindow& window)
{

	if (!initBackView)
	{
		backView = window.getDefaultView();
		initBackView = true;
	}

	window.setView(backView);
	window.draw(backGround);
	window.setView(mainView);

	for (auto it : walls)
	{
		it->DrawWall(window);
	}

	for (auto it : map.GetObjs())
	{
		window.draw(it->GetSprite());
	}

	for (auto it : map.GetTiles())
	{
		window.draw(it->GetSprite());
	}

	player.Draw(window);
	berry.Draw(window);
	thorny.Draw(window);
	
}

void GamePlay::Release()
{
}
