#pragma once
#include "SFML/Graphics.hpp"
#include "../Utils/UiMgr.h"
#include "../SceneMgr/SceneMgr.h"

using namespace sf;

class Framework
{
private:
	Vector2i resolution;
	SceneMgr sceneMgr;
	UiMgr ui;
	RenderWindow window;
	View* mainView;
	Image icon;
	Clock clock;
	TextureHolder textureHolder;

public:
	Framework();

	void init();
	void Update();
	void Draw();
};

