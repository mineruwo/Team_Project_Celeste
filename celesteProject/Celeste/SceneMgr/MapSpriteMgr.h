#pragma once
#include "SFML/Graphics.hpp"
#include "../Scene/Scene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Singleton.h"
using namespace sf;

class MapSpriteMgr : Singleton<MapSpriteMgr>
{
private:

	String tutorialBackGrndText;
	Sprite tutorialBackGrnd;
	String firstMapBackGrndText;
	Sprite firstMapBackGrnd;
	String backPackText;
	Sprite backPack;
	String cardText;
	Sprite card;
	String accentText;
	Sprite accent;
	String cardTopText;
	Sprite cardTop;
	String titleText;
	Sprite title;
	String tabText;
	Sprite tab;


	Sprite heartJam;  //Celeste-bin\Graphics\Atlases\Gui\collectables\heartgem\0
	Sprite runBackPack;


	String cTexture;
	String xTexture;
	Sprite cSprite;

	Sprite xSprite;



public:
	MapSpriteMgr();

	void LoadFile();
	void SetSpite();

	void InitTutirial();
	void InitFirstMap();
	void Update();
	void Draw(RenderWindow& window);



};

