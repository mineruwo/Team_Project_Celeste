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



void SaveCheck::moveCard(int select)
{
	characterCard[0].setPosition(cardCenter * 0.5, 60);
	characterCard[1].setPosition(cardCenter * 0.5, 360);
	characterCard[2].setPosition(cardCenter * 0.5, 660);
	characterTicket[0].setPosition(ticketCenter * 0.5, 60);
	characterTicket[1].setPosition(ticketCenter * 0.5, 360);
	characterTicket[2].setPosition(ticketCenter * 0.5, 660);

	berrySprite[0].setPosition(600, 100);
	deathSprite[0].setPosition(600, 200);
	berrySprite[1].setPosition(600, 400);
	deathSprite[1].setPosition(600, 500);
	berrySprite[2].setPosition(600, 700);
	deathSprite[2].setPosition(600, 800);
	
	characterCard[select].move(-400, 0);
	characterTicket[select].move(400, 0);
	berrySprite[select].move(400, 0);
	deathSprite[select].move(400, 0);
}


//void SaveCheck::MoveCard(int select, Time dt)
//{
//	if (isMove)
//	{
//		int offset = 300;
//
//		characterCard[select].move(offset * dt.asSeconds() * -1.f, 0);
//		characterTicket[select].move(offset * dt.asSeconds() * 1.f, 0);
//		berrySprite[select].move(offset * dt.asSeconds() * 1.f, 0);
//		deathSprite[select].move(offset * dt.asSeconds() * 1.f, 0);
//	}
//}
//
//void SaveCheck::RollBackCard(int select, Time dt)
//{
//	int offset = 300;
//
//	for (int i = 0; i < 3; i++)
//	{
//		if (i != select)
//		{
//			characterCard[select].move(offset * dt.asSeconds() * 1.f, 0);
//			characterTicket[select].move(offset * dt.asSeconds() * -1.f, 0);
//			berrySprite[select].move(offset * dt.asSeconds() * -1.f, 0);
//			deathSprite[select].move(offset * dt.asSeconds() * -1.f, 0);
//		}
//	}
//
//}




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

	if (InputMgr::GetKeyDown(Keyboard::Up))
	{
		if (selectLoad > 0)
		{
			selectLoad--;
			isMove = true;
			isRollback = true;
			//	MoveX = characterCard[selectLoad].getPosition().x;

			//	if (MoveX < 200)
			//	if (selectLoad == 0)
			//	{
			//		 RollX = characterCard[selectLoad + 1].getPosition().x;
			//	}
			//	else if (selectLoad != 0)
			//	{
			//		RollX = characterCard[selectLoad - 1].getPosition().x;
			//	}
		}


		switch (selectLoad)
		{
		case 0:
			//SaveCheck::RollBackCard(selectLoad, dt);
			//SaveCheck::MoveCard(selectLoad, dt);
			SaveCheck::moveCard(selectLoad);
			UiMgr::GetInstance().MoveSaveInfo(selectLoad);
			break;
		case 1:
			SaveCheck::moveCard(selectLoad);
			UiMgr::GetInstance().MoveSaveInfo(selectLoad);
			break;
		case 2:
			SaveCheck::moveCard(selectLoad);
			UiMgr::GetInstance().MoveSaveInfo(selectLoad);
			break;
		default:
			break;
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::Down))
	{
		if (selectLoad < 2)
		{
			selectLoad++;

		}


		switch (selectLoad)
		{
		case 0:
			//SaveCheck::RollBackCard(selectLoad, dt);
			//SaveCheck::MoveCard(selectLoad, dt);
			SaveCheck::moveCard(selectLoad);
			UiMgr::GetInstance().MoveSaveInfo(selectLoad);

			break;
		case 1:
			SaveCheck::moveCard(selectLoad);
			UiMgr::GetInstance().MoveSaveInfo(selectLoad);

			break;
		case 2:
			SaveCheck::moveCard(selectLoad);
			UiMgr::GetInstance().MoveSaveInfo(selectLoad);

			break;
		default:
			break;
		}

	}

	if (InputMgr::GetKeyDown(Keyboard::C))
	{

		switch (selectLoad)
		{
		case 0:
			Scene::NextScene(SceneID::ConfirmSelectedMapScene);
			SceneMgr::GetInstance().ChangeScene(SceneID::ConfirmSelectedMapScene);
			
			UiMgr::GetInstance().InitSceneUi(SceneID::ConfirmSelectedMapScene);
			GameInfoMgr::GetInstance().SetSaveDataIdx(selectLoad);
			/*Index = GameInfoMgr::GetInstance().getVecctorIndex()[];
			ConfirmSelectedMapScene::GetTutorialClear(Index);*/

			break;
		case 1:
			Scene::NextScene(SceneID::ConfirmSelectedMapScene);
			SceneMgr::GetInstance().ChangeScene(SceneID::ConfirmSelectedMapScene);
			UiMgr::GetInstance().InitSceneUi(SceneID::ConfirmSelectedMapScene);
			GameInfoMgr::GetInstance().SetSaveDataIdx(selectLoad);
			break;
		case 2:
			Scene::NextScene(SceneID::ConfirmSelectedMapScene);
			SceneMgr::GetInstance().ChangeScene(SceneID::ConfirmSelectedMapScene);
			UiMgr::GetInstance().InitSceneUi(SceneID::ConfirmSelectedMapScene);
			GameInfoMgr::GetInstance().SetSaveDataIdx(selectLoad);
			break;
		default:
			break;
		}


	}
	snow.Update(dt, window);

	//if (MoveX < 200)
	//{
	//	isMove = false;
	//}
	//if (RollX > 560)
	//{
	//	isRollback = false;
	//}
}

void SaveCheck::Draw(RenderWindow& window)
{
	window.draw(backGrnd);
	snow.Draw(window);
	window.draw(cSprite);
	window.draw(xSprite);
	window.draw(characterTicket[0]);
	window.draw(characterTicket[1]);
	window.draw(characterTicket[2]);
	window.draw(berrySprite[0]);
	window.draw(deathSprite[0]);
	window.draw(berrySprite[1]);
	window.draw(deathSprite[1]);
	window.draw(berrySprite[2]);
	window.draw(deathSprite[2]);
	UiMgr::GetInstance().SaveCheckDraw(window);
	window.draw(characterCard[0]);	
	window.draw(characterCard[1]);
	window.draw(characterCard[2]);


	
	
}


void SaveCheck::Release()
{
}

