#include "MainMenu.h"
#include "../SceneMgr/SceneMgr.h"

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
	climb.setTexture(TextureHolder::GetTexture(climbTexture));
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
	climb.setPosition(300, 200);
	option.setPosition(300,500);
	credit.setPosition(300, 600);
	exit.setPosition(300, 700);
	cSprite.setPosition(1600, 900);
	xSprite.setPosition(1700, 900);

	currScene = SceneID::MainMenu;

	snow.initFlake();
}

void MainMenu::SelectClimb(Time dt)
{
	option.setPosition(300, 500);
	credit.setPosition(300, 600);
	exit.setPosition(300, 700);
	
	float y = 200;
	if (climbBounce)
	{
		if (climbUp)
		{
			y -= dt.asSeconds() * 1000.f;
			climb.setPosition(300, y);
			if (y < 180)
			{
				climbUp = false;
			}
		}
		if (!climbUp)
		{
			y += dt.asSeconds() *1000.f;
			climb.setPosition(300, y);
			if (y > 200);
			{
				climbBounce = false;
			}
		}
	}
}

void MainMenu::SelectOption()
{
	climb.setPosition(300, 200);
	option.setPosition(320, 500);
	credit.setPosition(300, 600);
}

void MainMenu::Selectcredit()
{
	climb.setPosition(300, 200);
	option.setPosition(300, 500);
	credit.setPosition(320, 600);	
	exit.setPosition(300, 700);
}

void MainMenu::Selectexit()
{
	climb.setPosition(300, 200);
	option.setPosition(300, 500);
	credit.setPosition(300, 600);
	exit.setPosition(320, 700);
}


void MainMenu::Update(Time dt, RenderWindow& window)
{
	if (!isOption)
	{
		if (InputMgr::GetKeyDown(Keyboard::X))
		{
			// sceneID ¹Ù²ñ
			Scene::NextScene(SceneID::Title);
			//change/;
			SceneMgr::GetInstance().ChangeScene(SceneID::Title);
			UiMgr::GetInstance().InitSceneUi(SceneID::Title);
		}

		if (InputMgr::GetKeyDown(Keyboard::Up))
		{
			if (menuNum > 0)
			{
				menuNum--;
				climbBounce = true;
			}

		}
		switch (menuNum)
		{
		case 0: //climb
			MainMenu::SelectClimb(dt);
			UiMgr::GetInstance().MoveText(menuNum, dt);
			climbBounce = false;
			break;
		case 1: //option
			MainMenu::SelectOption();
			UiMgr::GetInstance().MoveText(menuNum, dt);
			break;
		case 2: // credit
			MainMenu::Selectcredit();
			UiMgr::GetInstance().MoveText(menuNum, dt);
			break;
		case 3: //exit
			MainMenu::Selectexit();
			UiMgr::GetInstance().MoveText(menuNum, dt);
			break;
		default:
			break;
		}

		if (InputMgr::GetKeyDown(Keyboard::Down))
		{
			if (menuNum < 3)
			{
				menuNum++;
			}
			switch (menuNum)
			{
			case 0: //climb
				MainMenu::SelectClimb(dt);
				UiMgr::GetInstance().MoveText(menuNum, dt);
				climbBounce = false;
				break;
			case 1: //option
				MainMenu::SelectOption();
				UiMgr::GetInstance().MoveText(menuNum, dt);
				break;
			case 2: // credit
				MainMenu::Selectcredit();
				UiMgr::GetInstance().MoveText(menuNum, dt);
				break;
			case 3: //exit
				MainMenu::Selectexit();
				UiMgr::GetInstance().MoveText(menuNum, dt);
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
				UiMgr::GetInstance().InitSceneUi(SceneID::SaveCheck);
				break;
			case 1:
				UiMgr::GetInstance().InitMainOption();
				isOption = true;
				break;
			case 2:
				Scene::NextScene(SceneID::Credits);
				SceneMgr::GetInstance().ChangeScene(SceneID::Credits);
				UiMgr::GetInstance().InitSceneUi(SceneID::Credits);
				break;
			case 3:
				window.close();
				break;
			default:
				break;
			}
		}
	}

	if (isOption)
	{
		if (InputMgr::GetKeyDown(Keyboard::X))
		{
			isOption = false;
		}

	}
	UiMgr::GetInstance().InitButtun();
	snow.Update(dt, window);
}

void MainMenu::Draw(RenderWindow& window)
{
	window.draw(menuBackGrnd);
	snow.Draw(window);
	if (!isOption)
	{
	window.draw(climb);
	window.draw(option);
	window.draw(credit);
	window.draw(exit);
	UiMgr::GetInstance().cxDraw(window);
	UiMgr::GetInstance().Draw(window);
	}
	if (isOption)
	{
		UiMgr::GetInstance().OptionDraw(window);
	}
	window.draw(cSprite);
	window.draw(xSprite);

}

void MainMenu::Release()
{
}
