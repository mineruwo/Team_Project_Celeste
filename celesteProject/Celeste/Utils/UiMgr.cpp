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
	
	SetText(mainMenuText[0], 30, Color::White, Vector2f(400, 400));
	SetText(mainMenuText[1], 30, Color::White, Vector2f(400, 500));
	SetText(mainMenuText[2], 30, Color::White, Vector2f(400, 600));
	SetText(mainMenuText[3], 30, Color::White, Vector2f(400, 700));

	mainMenuText[0].setString("climn");
	mainMenuText[1].setString("option");
	mainMenuText[2].setString("credit");
	mainMenuText[3].setString("exit");

}


void UiMgr::InitMainOption()
{
}

void UiMgr::InitPause()
{
}

void UiMgr::InitButtun()
{
	SetText(cText, 10, Color::White, Vector2f(1630, 900));
	SetText(xText, 10, Color::White, Vector2f(1730, 900));
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
	case SceneID::Option:
		UiMgr::InitMainOption();
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
	case SceneID::Option:
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





