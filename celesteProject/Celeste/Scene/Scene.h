#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class SceneID
{
	Title,
	MainMenu,
	Credits,
	SaveCheck,
	SelectMap,
	SelectChapter,
	GamePlay,
	Pause,
};


class Scene
{
protected:
	Font font;

private:
	SceneID currScene;

public:
	Scene();

	virtual void Init(Vector2i resolution);
	virtual void Update(Time dt, RenderWindow& window);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Release() {};

	SceneID* NextScene(SceneID Id);
	SceneID GetCurrScene();

};

