#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene/TItle.h"
#include"../Scene/Scene.h"

using namespace sf;

class SceneMgr
{

private:
	Scene* scene;
	SceneID currScene;


public:
	SceneMgr();
	~SceneMgr();
	void ChangeScene(SceneID Id);

	void SceneInit(Vector2i resolution);
	void SceneUpdate(Time dt, RenderWindow& window);
	void SceneDraw(RenderWindow& window);
	void SceneRelease();

};

