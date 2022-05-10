#include "UiMgr.h"

UiMgr::UiMgr()
{
	
}

void UiMgr::SetText(Text &text, unsigned int size, Color color, Vector2f positon)
{
	font.loadFromFile("Font/Eng.ttf");
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(positon);

}

void UiMgr::InitMainMenu()
{
	
	SetText(mainMenuText[0], 40, Color::White, Vector2f(360, 430));
	SetText(mainMenuText[1], 40, Color::White, Vector2f(400, 500));
	SetText(mainMenuText[2], 40, Color::White, Vector2f(400, 600));
	SetText(mainMenuText[3], 40, Color::White, Vector2f(400, 700));

	mainMenuText[0].setString("CLIMB");
	mainMenuText[1].setString("Option");
	mainMenuText[2].setString("Credit");
	mainMenuText[3].setString("Exit");

}


void UiMgr::InitMainOption()
{
	OptionText[0].setString("OPTION");
	OptionText[1].setString("Fullscreen");
	OptionText[2].setString("Window Scale");
	OptionText[3].setString("Vertical Sync");
	OptionText[4].setString("Music");
	OptionText[5].setString("Sound");

	SetText(OptionText[0], 100, Color::White, Vector2f(788,200));
	SetText(OptionText[1],50, Color::White, Vector2f(700,400));
	SetText(OptionText[2],50, Color::White, Vector2f(700, 500));
	SetText(OptionText[3],50, Color::White, Vector2f(700, 600));
	SetText(OptionText[4],50, Color::White, Vector2f(700, 700));
	SetText(OptionText[5],50, Color::White, Vector2f(700, 800));



}

void UiMgr::InitPause()
{
}

void UiMgr::InitButtun()
{
	SetText(cText, 10, Color::White, Vector2f(1500, 900));
	SetText(xText, 10, Color::White, Vector2f(1600, 900));

	cText.setString("Confirm");
	xText.setString("Back");
}

void UiMgr::MenuTextFlash()
{
}




void UiMgr::InitSceneUi(SceneID Id)
{
	
	currScene = Id;

	switch (Id)
	{
	case SceneID::Title:
		break;
	case SceneID::MainMenu:
		UiMgr::InitMainMenu();
		UiMgr::InitButtun();
		break;
	case SceneID::Credits:

		UiMgr::InitButtun();
		break;
	case SceneID::SaveCheck:

		UiMgr::InitButtun();
		break;
	case SceneID::SelectMap:

		UiMgr::InitButtun();
		break;
	case SceneID::SelectChapter:

		break;
	case SceneID::GamePlay:

		break;
	case SceneID::Pause:
		break;
	}
	
}

void UiMgr::MenuDraw(RenderWindow& window)
{
	for(int i = 0; i<4;i++)
		window.draw(mainMenuText[i]);
}

void UiMgr::OptionDraw(RenderWindow& window)
{
	for (int i = 0; i < 6; i++)
		window.draw(OptionText[i]);
}

void UiMgr::PauseDraw(RenderWindow& window)
{
}

void UiMgr::cxDraw(RenderWindow& window)
{
}


void UiMgr::Draw(RenderWindow& window)
{
	

	switch (currScene)
	{
	case SceneID::Title:
	break;
	case SceneID::MainMenu:	
		UiMgr::MenuDraw(window);
		break;
	case SceneID::Credits:
		break;
	case SceneID::SaveCheck:
		break;
	case SceneID::SelectMap:
		break;
	case SceneID::SelectChapter:
		break;
	case SceneID::GamePlay:
		break;
	case SceneID::Pause:
		break;
	}
}

void UiMgr::MoveText(int num , Time dt)
{
	InitMainMenu();
	switch (num)
	{
	case 0: //climb
		//InitMainMenu();
		SetText(mainMenuText[0], 50, Color::White, Vector2f(360, 420));
		mainMenuText[0].setFillColor(Color::Green);
		break;
	case 1: //option
	//	InitMainMenu();
		SetText(mainMenuText[1], 50, Color::White, Vector2f(420, 500));
		mainMenuText[1].setFillColor(Color::Green);
		break;
	case 2: // credit
		//InitMainMenu();
		SetText(mainMenuText[2], 50, Color::White, Vector2f(420, 600));
		mainMenuText[2].setFillColor(Color::Green);
		break;
	case 3: //exit
	//	InitMainMenu();
		SetText(mainMenuText[3], 50, Color::White, Vector2f(420, 700));
		mainMenuText[3].setFillColor(Color::Green);
		break;
	default:
		break;
	}
}



