#include "MainMenu.h"
#include "../SceneMgr/SceneMgr.h"

MainMenu::MainMenu()
{
}

void MainMenu::Init(Vector2i resolution)
{
	menuBackGrndTexture = "Graphics/backgrnd.png";
	ClimbTexture = "Graphics/Atlases/Gui/menu/start.png";
	optionTexture = "Graphics/Atlases/Gui/menu/options.png";
	CreditTexture = "Graphics/Atlases/Gui/menu/credits.png";
	exitTexture = "Graphics/Atlases/Gui/menu/exit.png";
	cTexture = "Graphics/Atlases/Gui/controls/keyboard/c.png";
	xTexture = "Graphics/Atlases/Gui/controls/keyboard/x.png";


	menuBackGrnd.setTexture(TextureHolder::GetTexture(menuBackGrndTexture));
	Climn.setTexture(TextureHolder::GetTexture(ClimbTexture));
	option.setTexture(TextureHolder::GetTexture(optionTexture));
	credit.setTexture(TextureHolder::GetTexture(CreditTexture));
	exit.setTexture(TextureHolder::GetTexture(exitTexture));
	cSprite.setTexture(TextureHolder::GetTexture(cTexture));
	xSprite.setTexture(TextureHolder::GetTexture(xTexture));

	option.setScale(0.5f, 0.5f);
	credit.setScale(0.5f, 0.5f);
	exit.setScale(0.5f, 0.5f);
	cSprite.setScale(0.5f, 0.5f);
	xSprite.setScale(0.5f, 0.5f);

	menuBackGrnd.setPosition(0,0);
	Climn.setPosition(300, 150);
	option.setPosition(300,500);
	credit.setPosition(300, 600);
	exit.setPosition(300, 700);
	cSprite.setPosition(1600, 900);
	xSprite.setPosition(1700, 900);

	currScene = SceneID::MainMenu;
}

void MainMenu::Update(Time dt, RenderWindow& window)
{
	if (InputMgr::GetKeyDown(Keyboard::X))
	{
		// sceneID ¹Ù²ñ
		Scene::NextScene(SceneID::Title);
		//change/;
		SceneMgr::GetInstance().ChangeScene(SceneID::Title);

	}

	
}

void MainMenu::Draw(RenderWindow& window)
{
	window.draw(menuBackGrnd);
	window.draw(Climn);
	window.draw(option);
	window.draw(credit);
	window.draw(exit);
	window.draw(cSprite);
	window.draw(xSprite);

}

void MainMenu::Release()
{
}
