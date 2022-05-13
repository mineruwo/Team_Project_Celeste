#pragma once
#include "SFML/Graphics.hpp"
#include "../Scene/Scene.h"
#include "../Utils/GameInfoMgr.h"
#include "Singleton.h"
#include <vector>
#include <random>
#include <sstream>
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

	int IndexCount;

	char berry[3][30];
	char deathCount[3][30];
	char playTime[3][30];
	
	Text berryText[3];
	Text deathText[3];
	Text playTimeText[3];

	float pt;
	int hour;
	int minute;
	int second;

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
	void MoveSaveInfo(int select);
	void InitSaveCheckUi();

	void InitSceneUi(SceneID Id);

	void MenuDraw(RenderWindow& window);
	void OptionDraw(RenderWindow& window);
	void CreditDraw(RenderWindow& window);
	void PauseDraw(RenderWindow& window);
	void cxDraw(RenderWindow& window);

	void SaveCheckDraw(RenderWindow& window);


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

