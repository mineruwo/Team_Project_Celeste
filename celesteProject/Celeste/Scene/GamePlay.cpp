#include "GamePlay.h"

GamePlay::GamePlay():currScene(SceneID::GamePlay)
{
	bats = bat.GetBatRect();
	
}

//GamePlay::~GamePlay()
//{
//}

void GamePlay::CreateWalls()
{
	for (auto v : walls)
	{
		delete v;
	}

	walls.clear();

	Wall* wallUp = new Wall(bats);
	walls.push_back(wallUp);

}

void GamePlay::Init(Vector2i resolution)
{

	GamePlay::CreateWalls();
	//캐릭터 , 맵 ,오브젝트 초기화
	player.Init();

	currScene = SceneID::GamePlay;
}

void GamePlay::Update(Time dt, RenderWindow& window)
{
	//플레이 상호작용 
	if (dt.asSeconds() <= 1.f / 200.f)
	{
		InputMgr::Update(dt.asSeconds());
		player.Update(dt.asSeconds(), walls);
		// bat.Update(walls);
	}


	//if (InputMgr::GetKeyDown(Keyboard::Escape))
	//{
	//	// sceneID 바뀜
	//	Scene::NextScene(SceneID::);
	//	//change/;
	//	SceneMgr::GetInstance().ChangeScene(SceneID::);
	//}

	
}

void GamePlay::Draw(RenderWindow& window)
{
	window.draw(bat.GetShape());
	player.Draw(window);
	
}

void GamePlay::Release()
{
}
