#pragma once
#include "SFML/Graphics.hpp"
#include "../Scene/Scene.h"
#include "Singleton.h"
#include <vector>
#include <random>
using namespace sf;

class UiMgr : public Singleton<UiMgr>
{

private:

	FloatRect optionRect;
	Vector2f optionCenter;

	SceneID currScene;
	Font font;

	Text mainMenuText[4]; // 오르기 옵션 크래딧 종료
	Text OptionText[6]; // 옵션 전체 창비율 수직동기화 음악 소리
	Text pauseText[7]; // 일시중지 계속 다시 옵션 저장 챕터 맵

	Text cText;
	Text xText;




public:
	UiMgr();
	void SetText(Text &text, unsigned int size, Color color , Vector2f positon);

	void InitMainMenu();
	void InitMainOption();
	void InitPause();
	void InitButtun();

	void MenuTextFlash();
	

	void InitSceneUi(SceneID Id);

	void MenuDraw(RenderWindow& window);
	void OptionDraw(RenderWindow& window);
	void PauseDraw(RenderWindow& window);
	void cxDraw(RenderWindow& window);

	void Draw(RenderWindow& window);
	void MoveText(int num, Time dt);
};

