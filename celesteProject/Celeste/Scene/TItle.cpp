#include "TItle.h"

void TItle::Init(Vector2i resolution)
{
	backGrndName = "Graphics/Atlases/Core/01.png";
	logoName = "Graphics/Atlases/Gui/logo.png";
	cName = "Graphics/Atlases/Gui/controls/keyboard/c.png";

	backGrnd.setTexture(TextureHolder::GetTexture(backGrndName));
	logoSprite.setTexture(TextureHolder::GetTexture(logoName));
	cSprite.setTexture(TextureHolder::GetTexture(cName));

	titleRect = logoSprite.getGlobalBounds();
	Vector2f titleCenter = Vector2f(
		VideoMode::getDesktopMode().width - titleRect.width, VideoMode::getDesktopMode().height - titleRect.height);

	backGrnd.setScale(2.f, 2.f);
	
	backGrnd.setPosition(0, 0);
	logoSprite.setPosition(titleCenter);
	cSprite.setPosition(1700, 900);

	currScene = SceneID::Title;
}

void TItle::Update()
{
	if (InputMgr::GetKeyDown(Keyboard::C))
	{
		Scene::NextScene(SceneID::MainMenu);
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
