#include "GamePlay.h"

GamePlay::GamePlay():currScene(SceneID::GamePlay)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init(Vector2i resolution)
{


	//ĳ���� , �� ,������Ʈ �ʱ�ȭ


	currScene = SceneID::GamePlay;
}

void GamePlay::Update(Time dt, RenderWindow& window)
{
	//�÷��� ��ȣ�ۿ� 
	player.Update(dt,walls);


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
	player.Draw(window);
	
}

void GamePlay::Release()
{
}
