#include "SaveCheck.h"

SaveCheck::SaveCheck()
	:currScene(SceneID::SaveCheck)
{
}

void SaveCheck::Init(Vector2i resolution)
{
	backGrndTexture = "Graphics/backgrnd.png";
	characterCardTexture = "Graphics/Atlases/FileSelect/card.png";
	characterTicketTexture = "Graphics/Atlases/FileSelect/ticket.png";
	cTexture = "Graphics/Atlases/Gui/controls/keyboard/c.png";
	xTexture = "Graphics/Atlases/Gui/controls/keyboard/x.png";

	backGrnd.setTexture(TextureHolder::GetTexture(backGrndTexture));
	for (int i = 0; i < 3; i++)
	{
		characterCard[i].setTexture(TextureHolder::GetTexture(characterCardTexture));
		characterTicket[i].setTexture(TextureHolder::GetTexture(characterTicketTexture));
	}
	cSprite.setTexture(TextureHolder::GetTexture(cTexture));
	xSprite.setTexture(TextureHolder::GetTexture(xTexture));

	cSprite.setScale(0.5f, 0.5f);
	xSprite.setScale(0.5f, 0.5f);
	
	cardCenter = (VideoMode::getDesktopMode().width - characterCard->getGlobalBounds().width);
	ticketCenter = (VideoMode::getDesktopMode().width - characterTicket->getGlobalBounds().width);


	backGrnd.setPosition(0, 0);

	characterCard[0].setPosition(cardCenter*0.5, 60);
	characterCard[1].setPosition(cardCenter * 0.5, 360);
	characterCard[2].setPosition(cardCenter * 0.5, 660);
	characterTicket[0].setPosition(ticketCenter*0.5, 60);
	characterTicket[1].setPosition(ticketCenter * 0.5, 360);
	characterTicket[2].setPosition(ticketCenter * 0.5, 660);

	cSprite.setPosition(1600, 900);
	xSprite.setPosition(1700, 900);


	cSprite.setTexture(TextureHolder::GetTexture(cTexture));
	xSprite.setTexture(TextureHolder::GetTexture(xTexture));



	currScene = SceneID::SaveCheck;
}

void SaveCheck::Update(Time dt, RenderWindow& window)
{
	if (InputMgr::GetKeyDown(Keyboard::X))
	{
		// sceneID ¹Ù²ñ
		//Scene::NextScene(SceneID::MainMenu);
		SceneMgr::GetInstance().GetScene().NextScene(SceneID::MainMenu);

		//change/;
		SceneMgr::GetInstance().ChangeScene(SceneID::MainMenu);
		UiMgr::GetInstance().InitSceneUi(SceneID::MainMenu);

	}

	if (InputMgr::GetKeyDown(Keyboard::C))
	{
		// sceneID ¹Ù²ñ
		//Scene::NextScene(SceneID::GamePlay);
		SceneMgr::GetInstance().GetScene().NextScene(SceneID::GamePlay);

		//change/;
		SceneMgr::GetInstance().ChangeScene(SceneID::GamePlay);
		UiMgr::GetInstance().InitSceneUi(SceneID::GamePlay);
	}
}

void SaveCheck::Draw(RenderWindow& window)
{
	window.draw(backGrnd);
	window.draw(characterTicket[0]);
	window.draw(characterTicket[1]);
	window.draw(characterTicket[2]);
	window.draw(characterCard[0]);	
	window.draw(characterCard[1]);
	window.draw(characterCard[2]);
	window.draw(cSprite);
	window.draw(xSprite);
}

void SaveCheck::Release()
{
}
