#include "ConfirmSelectedMapScene.h"

ConfirmSelectedMapScene::ConfirmSelectedMapScene()
	:currScene(SceneID::ConfirmSelectedMapScene)
{	
}

void ConfirmSelectedMapScene::GetTutorialClear()
{
	firstMapOnOff = GameInfoMgr::GetInstance().GetTutoclear();
}

void ConfirmSelectedMapScene::Init(Vector2i resolution)

{
	SelectMapSpriteMgr::GetInstance().LoadFile();
	SelectMapSpriteMgr::GetInstance().SetSpite();
	SelectMapSpriteMgr::GetInstance().InitTutirial();

	currScene = SceneID::ConfirmSelectedMapScene;
	snow.initFlake();
}

void ConfirmSelectedMapScene::Update(Time dt, RenderWindow& window)
{
	if (firstMapOnOff)
	{
		if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			if (firstMapOnOff = 1 && tutorial)
			{
				SelectMapSpriteMgr::GetInstance().InitFirstMap();
				tutorial = true;
				first = false;
			}
		}
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			if (firstMapOnOff = 1 && first)
			{
				SelectMapSpriteMgr::GetInstance().InitTutirial();
				tutorial = false;
				first = true;
			}
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::X))
	{
		// sceneID ¹Ù²ñ
		Scene::NextScene(SceneID::SaveCheck);
		//change/;
		SceneMgr::GetInstance().ChangeScene(SceneID::SaveCheck);
		UiMgr::GetInstance().InitSceneUi(SceneID::SaveCheck);
	}

	if (InputMgr::GetKeyDown(Keyboard::C))
	{
		if (tutorial && !first)
		{
			Scene::NextScene(SceneID::GamePlay);
			SceneMgr::GetInstance().ChangeScene(SceneID::GamePlay);
			UiMgr::GetInstance().InitSceneUi(SceneID::GamePlay);
			//µàÅä¸®¾ó¸ÊÀ¸·Î
		}
		if (!tutorial && first)
		{
			Scene::NextScene(SceneID::GamePlay);
			//SceneMgr::GetInstance().GetScene().NextScene(SceneID::GamePlay);
			//change/;
			SceneMgr::GetInstance().ChangeScene(SceneID::GamePlay);
			UiMgr::GetInstance().InitSceneUi(SceneID::GamePlay);
		//	1½ºÅ×ÀÌÁö·Î
		}
	}

	snow.Update(dt, window);

}

void ConfirmSelectedMapScene::Draw(RenderWindow& window)
{
	if (tutorial && !first)
	{
		SelectMapSpriteMgr::GetInstance().DrawTutorial(window);
	}
	if (!tutorial && first)
	{
		SelectMapSpriteMgr::GetInstance().DrawFirst(window);
	}
	snow.Draw(window);
}

void ConfirmSelectedMapScene::Release()
{
}
