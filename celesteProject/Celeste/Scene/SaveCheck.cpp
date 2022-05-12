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
	berryTexture = "Graphics/Atlases/Gui/collectables/strawberry.png";
	deathTexture = "Graphics/Atlases/Gui/collectables/skullBlue.png";
	backGrnd.setTexture(TextureHolder::GetTexture(backGrndTexture));
	for (int i = 0; i < 3; i++)
	{
		characterCard[i].setTexture(TextureHolder::GetTexture(characterCardTexture));
		characterTicket[i].setTexture(TextureHolder::GetTexture(characterTicketTexture));
		berrySprite[i].setTexture(TextureHolder::GetTexture(berryTexture));
		deathSprite[i].setTexture(TextureHolder::GetTexture(deathTexture));
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

	berrySprite[0].setPosition(600, 100);
	deathSprite[0].setPosition(600, 200);
	berrySprite[1].setPosition(600, 400);
	deathSprite[1].setPosition(600, 500);
	berrySprite[2].setPosition(600, 700);
	deathSprite[2].setPosition(600, 800);

	cSprite.setTexture(TextureHolder::GetTexture(cTexture));
	xSprite.setTexture(TextureHolder::GetTexture(xTexture));

	UiMgr::GetInstance().InitSaveCheckUi();


	currScene = SceneID::SaveCheck;
	snow.initFlake();
}

void SaveCheck::Update(Time dt, RenderWindow& window)
{
	if (InputMgr::GetKeyDown(Keyboard::X))
	{
		// sceneID �ٲ�
		//Scene::NextScene(SceneID::MainMenu);
		SceneMgr::GetInstance().GetScene().NextScene(SceneID::MainMenu);

		//change/;
		SceneMgr::GetInstance().ChangeScene(SceneID::MainMenu);
		UiMgr::GetInstance().InitSceneUi(SceneID::MainMenu);

	}

	if (InputMgr::GetKeyDown(Keyboard::C))
	{
		// sceneID �ٲ�
		//Scene::NextScene(SceneID::GamePlay);
		SceneMgr::GetInstance().GetScene().NextScene(SceneID::ConfirmSelectedMapScene);

		//change/;
		SceneMgr::GetInstance().ChangeScene(SceneID::ConfirmSelectedMapScene);
		UiMgr::GetInstance().InitSceneUi(SceneID::ConfirmSelectedMapScene
		);
	}
	snow.Update(dt, window);
}

void SaveCheck::Draw(RenderWindow& window)
{
	window.draw(backGrnd);
	snow.Draw(window);
	window.draw(characterTicket[0]);
	window.draw(characterTicket[1]);
	window.draw(characterTicket[2]);
	UiMgr::GetInstance().SaveCheckDraw(window);
	//window.draw(characterCard[0]);	
	//window.draw(characterCard[1]);
	//window.draw(characterCard[2]);
	window.draw(cSprite);
	window.draw(xSprite);
	window.draw(berrySprite[0]);
	window.draw(deathSprite[0]);
	window.draw(berrySprite[1]);
	window.draw(deathSprite[1]);
	window.draw(berrySprite[2]);
	window.draw(deathSprite[2]);
	
	
}

void SaveCheck::Release()
{
}