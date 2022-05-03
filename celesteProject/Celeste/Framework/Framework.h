#pragma once
#include "SFML/Graphics.hpp"
#include "../SceneMgr/SceneMgr.h"

using namespace sf;

class Framework
{
private:
	Vector2i resolution;
	SceneMgr sceneMgr;
	RenderWindow window;
	Image icon;
	Clock clock;
	TextureHolder textureHolder;

public:
	Framework();

	void init();
	void Update();
	void Draw();
};

