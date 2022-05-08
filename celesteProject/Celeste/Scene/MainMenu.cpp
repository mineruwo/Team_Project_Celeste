#include "MainMenu.h"
#include "../SceneMgr/SceneMgr.h"
#include "../Utils/UiMgr.h"

MainMenu::MainMenu():currScene(SceneID::MainMenu)
{
}

void MainMenu::Init(Vector2i resolution)
{
	menuBackGrndTexture = "Graphics/backgrnd.png";
	climbTexture = "Graphics/Atlases/Gui/menu/start.png";
	optionTexture = "Graphics/Atlases/Gui/menu/options.png";
	creditTexture = "Graphics/Atlases/Gui/menu/credits.png";
	exitTexture = "Graphics/Atlases/Gui/menu/exit.png";
	cTexture = "Graphics/Atlases/Gui/controls/keyboard/c.png";
	xTexture = "Graphics/Atlases/Gui/controls/keyboard/x.png";


	menuBackGrnd.setTexture(TextureHolder::GetTexture(menuBackGrndTexture));
	climn.setTexture(TextureHolder::GetTexture(climbTexture));
	option.setTexture(TextureHolder::GetTexture(optionTexture));
	credit.setTexture(TextureHolder::GetTexture(creditTexture));
	exit.setTexture(TextureHolder::GetTexture(exitTexture));
	cSprite.setTexture(TextureHolder::GetTexture(cTexture));
	xSprite.setTexture(TextureHolder::GetTexture(xTexture));

	option.setScale(0.5f, 0.5f);
	credit.setScale(0.5f, 0.5f);
	exit.setScale(0.5f, 0.5f);
	cSprite.setScale(0.5f, 0.5f);
	xSprite.setScale(0.5f, 0.5f);

	menuBackGrnd.setPosition(0,0);
	climn.setPosition(300, 150);
	option.setPosition(300,500);
	credit.setPosition(300, 600);
	exit.setPosition(300, 700);
	cSprite.setPosition(1600, 900);
	xSprite.setPosition(1700, 900);

	currScene = SceneID::MainMenu;
}

void MainMenu::SelctClimn(Time dt)
{

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

	if (InputMgr::GetKeyDown(Keyboard::Up))
	{
		if (menuNum > 0)
		{
			menuNum--;
		}

		switch (menuNum)
		{

		case 0:
			climn.setPosition(300, 160);
			option.setPosition(300, 500);
			credit.setPosition(300, 600);
			exit.setPosition(300, 700);
			break;
		case 1:
			option.setPosition(320, 500);
			climn.setPosition(300, 150);
			credit.setPosition(300, 600);
			exit.setPosition(300, 700);
			break;
		case 2:
			credit.setPosition(320, 600);
			climn.setPosition(300, 150);
			option.setPosition(300, 500);
			exit.setPosition(300, 700);
		case 3:
			exit.setPosition(320, 700);
			climn.setPosition(300, 150);
			option.setPosition(300, 500);
			credit.setPosition(300, 600);
			break;
		default:
			break;
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::Down))
	{
		if (menuNum < 3)
		{
			menuNum++;
		}
		switch (menuNum)
		{

		case 0:
			climn.setPosition(300, 160);
			option.setPosition(300, 500);
			credit.setPosition(300, 600);
			exit.setPosition(300, 700);
			break;
		case 1:
			option.setPosition(320, 500);
			climn.setPosition(300, 150);
			credit.setPosition(300, 600);
			exit.setPosition(300, 700);
			break;
		case 2:
			credit.setPosition(320, 600);
			climn.setPosition(300, 150);
			option.setPosition(300, 500);
			exit.setPosition(300, 700);
		case 3:
			exit.setPosition(320, 700);
			climn.setPosition(300, 150);
			option.setPosition(300, 500);
			credit.setPosition(300, 600);
			break;
		default:
			break;
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::C))
	{
		switch (menuNum)
		{

		case 0:
			Scene::NextScene(SceneID::SaveCheck);
			SceneMgr::GetInstance().ChangeScene(SceneID::SaveCheck);
			break;
		case 1:
			Scene::NextScene(SceneID::Option);
			SceneMgr::GetInstance().ChangeScene(SceneID::Option);
			break;
		case 2:
			Scene::NextScene(SceneID::Credits);
			SceneMgr::GetInstance().ChangeScene(SceneID::Credits);
			break;
		case 3:
			window.close();
			break;
		default:
			break;
		}
	}
}

void MainMenu::Draw(RenderWindow& window)
{
	window.draw(menuBackGrnd);
	window.draw(climn);
	window.draw(option);
	window.draw(credit);
	window.draw(exit);
	window.draw(cSprite);
	window.draw(xSprite);
	

}

void MainMenu::Release()
{
}
