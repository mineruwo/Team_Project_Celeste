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
	Text optionText[6]; // �ɼ� ��ü â���� ��������ȭ ���� �Ҹ�
	Text pauseText[7]; // �Ͻ����� ��� �ٽ� �ɼ� ���� é�� ��

	
	Text screenSize;
	Text windowScale;
	Text VerticalSync;
	Text MusicControl;
	Text SoundControl;

	Text creditContent;
	
	Text cText;
	Text xText;

	/*bool fullScreen = true;
	int Scale = 0;
	bool Sync = true;
	int musicVolume;
	int soundVolume;*/




public:
	UiMgr();
	void SetText(Text &text, unsigned int size, Color color , Vector2f positon);

	void InitMainMenu();
	void InitMainOption();
	void InitCredit();
	void InitPause();
	void InitButtun();

	void MenuTextFlash();
	

	void InitSceneUi(SceneID Id);

	void MenuDraw(RenderWindow& window);
	void OptionDraw(RenderWindow& window);
	void CreditDraw(RenderWindow& window);
	void PauseDraw(RenderWindow& window);
	void cxDraw(RenderWindow& window);

	void Draw(RenderWindow& window);
	void MoveText(int num, Time dt);

	/*
	void optionUpdate();

	void Screen();
	void Scale();
	void Sync();
	void Music();
	void Sound();
*/
};

