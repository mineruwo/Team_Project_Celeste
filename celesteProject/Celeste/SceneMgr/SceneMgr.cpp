#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	scene = new TItle;
	currScene = SceneID::Title;
}

SceneMgr::~SceneMgr()
{
	delete scene;
}

void SceneMgr::ChangeScene(SceneID Id)
{
	/*if (nullptr != scene)
	{
		delete scene;
		scene = nullptr;
	}*/

	switch (Id)
	{
	case SceneID::Title:
		scene = new TItle;
		currScene = SceneID::Title;
		SceneMgr::SceneInit(resolution);
		break;
	case SceneID::MainMenu:
		scene = new MainMenu;
		currScene = SceneID::MainMenu;
		SceneMgr::SceneInit(resolution);
		break;
	case SceneID::SaveCheck:
		scene = new SaveCheck;
		currScene = SceneID::SaveCheck;
		SceneMgr::SceneInit(resolution);
		break;
	case SceneID::ConfirmSelectedMapScene:
		scene = new ConfirmSelectedMapScene;
		currScene = SceneID::ConfirmSelectedMapScene;
		SceneMgr::SceneInit(resolution);
		break;
	case SceneID::GamePlay:
		scene = new GamePlay;
		currScene = SceneID::GamePlay;
		SceneMgr::SceneInit(resolution);
		break;
	}

	Ui.InitSceneUi(Id);
}

void SceneMgr::SceneInit(Vector2i resolution)
{
	scene->Init(resolution);
}

void SceneMgr::SceneUpdate(Time dt, RenderWindow& window)
{
	scene->Update(dt, window);
	
}

void SceneMgr::SceneDraw(RenderWindow& window)
{
	scene->Draw(window);
	
}

void SceneMgr::SceneRelease()
{
	scene->Release();
}

Scene& SceneMgr::GetScene()
{
	return *scene;
}


