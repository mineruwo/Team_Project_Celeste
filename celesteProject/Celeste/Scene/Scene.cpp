#include "Scene.h"


Scene::Scene()
{
}

void Scene::Init(Vector2i resolution)
{
}

void Scene::Update(Time dt, RenderWindow& window)
{
}

void Scene::Draw(sf::RenderWindow& window)
{
}

SceneID Scene::NextScene(SceneID Id)
{
	currScene = Id;
	return currScene;
}

SceneID Scene::GetCurrScene()
{
	return Scene::currScene;
}
