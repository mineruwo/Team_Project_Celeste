#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene/TItle.h"
#include"../Scene/Scene.h"
#include"../Scene/MainMenu.h"
#include"../Utils/Singleton.h"
#include"../Scene/SaveCheck.h"
#include"../Utils/UiMgr.h"

using namespace sf;

class SceneMgr : public Singleton<SceneMgr>
{

private:
	Scene* scene;
	UiMgr Ui;
	SceneID currScene;
	Vector2i resolution;

public:
	SceneMgr();
	~SceneMgr();
	void ChangeScene(SceneID Id);

	void SceneInit(Vector2i resolution);
	void SceneUpdate(Time dt, RenderWindow& window);
	void SceneDraw(RenderWindow& window);
	void SceneRelease();

};

