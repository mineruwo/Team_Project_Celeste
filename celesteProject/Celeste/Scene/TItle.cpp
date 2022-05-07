#include "TItle.h"


TItle::TItle():currScene(SceneID::Title)
{
}

void TItle::Init(Vector2i resolution)
{
	backGrndTexture = "Graphics/Atlases/Core/01.png";
	logoTexture = "Graphics/Atlases/Gui/logo.png";
	cTexture = "Graphics/Atlases/Gui/controls/keyboard/c.png";

	backGrnd.setTexture(TextureHolder::GetTexture(backGrndTexture));
	logoSprite.setTexture(TextureHolder::GetTexture(logoTexture));
	cSprite.setTexture(TextureHolder::GetTexture(cTexture));

	titleRect = logoSprite.getGlobalBounds();
	titleCenter = Vector2f(
		VideoMode::getDesktopMode().width - titleRect.width, VideoMode::getDesktopMode().height - titleRect.height);

	backGrnd.setScale(2.f, 2.f);
	
	backGrnd.setPosition(0, 0);
	logoSprite.setPosition(titleCenter);
	cSprite.setPosition(1700, 900);

	currScene = SceneID::Title;
}

void TItle::Update(Time dt, RenderWindow& window)
{
	if (InputMgr::GetKeyDown(Keyboard::C))
	{
		// sceneID ¹Ù²ñ
		Scene::NextScene(SceneID::MainMenu);
		//change/;
		SceneMgr::GetInstance().ChangeScene(SceneID::MainMenu);
		UiMgr::GetInstance().InitSceneUi(SceneID::MainMenu);
	}
}

void TItle::Draw(RenderWindow& window)
{
	window.draw(backGrnd);
	window.draw(logoSprite);
	window.draw(cSprite);
}

void TItle::Release()
{
}
