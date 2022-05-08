#include "GamePlay.h"

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init(Vector2i resolution)
{

	//캐릭터 , 맵 ,오브젝트 초기화


	currScene = SceneID::GamePlay;
}

void GamePlay::Update(Time dt, RenderWindow& window)
{
	//플레이 상호작용 



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

}

void GamePlay::Release()
{
}
