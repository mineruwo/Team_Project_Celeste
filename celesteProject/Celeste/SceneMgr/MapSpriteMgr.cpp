#include "MapSpriteMgr.h"

MapSpriteMgr::MapSpriteMgr()
{
}

void MapSpriteMgr::LoadFile()
{
	tutorialBackGrndText = "Graphics/map/prolog.png";
	firstMapBackGrndText = "Graphics/map/ch1.png";
	backPackText = "Graphics/Atlases/Gui/menu/play.png";
	cardText = "Graphics/Atlases/Gui/areaselec/card.png";
	accentText = "Graphics/Atlases/Gui/areaselec/card.png";
	cardTopText = "Graphics/Atlases/Gui/areaselec/cardtop.png";
	titleText = "Graphics/Atlases/Gui/areaselec/title.png";
	tabText = "Graphics/Atlases/Gui/areaselec/tab.png";
	cTexture = "Graphics/Atlases/Gui/controls/keyboard/c.png";
	xTexture = "Graphics/Atlases/Gui/controls/keyboard/x.png";
}

void MapSpriteMgr::SetSpite()
{	
	tutorialBackGrnd.setTexture(TextureHolder::GetTexture(tutorialBackGrndText));
	firstMapBackGrnd.setTexture(TextureHolder::GetTexture(firstMapBackGrndText));
	backPack.setTexture(TextureHolder::GetTexture(backPackText));
	card.setTexture(TextureHolder::GetTexture(cardText));
	accent.setTexture(TextureHolder::GetTexture(accentText));
	cardTop.setTexture(TextureHolder::GetTexture(cardTopText));
	title.setTexture(TextureHolder::GetTexture(titleText));
	tab.setTexture(TextureHolder::GetTexture(tabText));
	cSprite.setTexture(TextureHolder::GetTexture(cTexture));
	xSprite.setTexture(TextureHolder::GetTexture(xTexture));

	cSprite.setScale(0.5f, 0.5f);
	xSprite.setScale(0.5f, 0.5f);



}


void MapSpriteMgr::InitTutirial()
{
	tutorialBackGrnd.setPosition(0, 0);
	backPack.setPosition(1400, 600);
	card.setPosition(900, 100);
	accent.setPosition(890, 50);
	cardTop.setPosition(900, 100);
	title.setPosition(890, 50);
	tab.setPosition(1300, 600);
	cSprite.setPosition(1600, 900);
	xSprite.setPosition(1700, 900);



}


void MapSpriteMgr::InitFirstMap()
{
	firstMapBackGrnd.setPosition(0,0);
	backPack.setPosition(1400,600);
	card.setPosition(900,100);
	accent.setPosition(890,50);
	cardTop.setPosition(900,100);
	title.setPosition(890,50);
	tab.setPosition(1300,600);
	cSprite.setPosition(1600, 900);
	xSprite.setPosition(1700, 900);
}

void MapSpriteMgr::Update()
{
}

void MapSpriteMgr::Draw(RenderWindow& window)
{
	window.draw(firstMapBackGrnd);
	window.draw(backPack);
	window.draw(card);
	window.draw(accent);
	window.draw(cardTop);
	window.draw(title);
	window.draw(tab);
	window.draw(cSprite);
	window.draw(xSprite);

}
