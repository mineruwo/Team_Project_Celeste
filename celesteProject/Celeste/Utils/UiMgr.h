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

	Text mainMenuText[4]; // ������ �ɼ� ũ���� ����
	Text OptionText[6]; // �ɼ� ��ü â���� ��������ȭ ���� �Ҹ�
	Text pauseText[7]; // �Ͻ����� ��� �ٽ� �ɼ� ���� é�� ��

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

