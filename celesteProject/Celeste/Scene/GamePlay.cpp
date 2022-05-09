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
	//ĳ���� , �� ,������Ʈ �ʱ�ȭ
	player.Init();

	currScene = SceneID::GamePlay;
}

void GamePlay::Update(Time dt, RenderWindow& window)
{
	//�÷��� ��ȣ�ۿ� 
	if (dt.asSeconds() <= 1.f / 200.f)
	{
		InputMgr::Update(dt.asSeconds());
		player.Update(dt.asSeconds(), walls);
		// bat.Update(walls);
	}


	//if (InputMgr::GetKeyDown(Keyboard::Escape))
	//{
	//	// sceneID �ٲ�
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
