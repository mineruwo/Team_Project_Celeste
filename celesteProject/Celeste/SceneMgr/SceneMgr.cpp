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
//	delete scene;

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
	//case SceneID::Option:
	//	scene = new ;
	//	currScene = SceneID::Option;
	//	break;
	//case SceneID::Credits:
	//	scene = new ;
	//	currScene = SceneID::Credits;
	//	break;
	case SceneID::SaveCheck:
		scene = new SaveCheck;
		currScene = SceneID::SaveCheck;
		SceneMgr::SceneInit(resolution);
		break;
	//case SceneID::SelectMap:
	//	scene = new ;
	//	currScene = SceneID::SelectMap;
	//	break;
	//case SceneID::SelectChapter:
	//	scene = new ;
	//	currScene = SceneID::SelectChapter;
	//	break;
	//case SceneID::GamePlay:
	//	scene = new ;
	//	currScene = SceneID::GamePlay;
	//	break;
	//case SceneID::Pause:
	//	scene = new ;
	//	currScene = SceneID::Pause;
	//	break;
	
	}
}

void SceneMgr::SceneInit(Vector2i resolution)
{
	scene->Init(resolution);
}

void SceneMgr::SceneUpdate(Time dt, RenderWindow& window)
{
	scene->Update(dt, window);
	if (scene->GetCurrScene() != currScene)
	{
		ChangeScene(scene->GetCurrScene());

	}
}

void SceneMgr::SceneDraw(RenderWindow& window)
{
	window.clear();
	scene->Draw(window);
	window.display();
}

void SceneMgr::SceneRelease()
{
	scene->Release();
}


