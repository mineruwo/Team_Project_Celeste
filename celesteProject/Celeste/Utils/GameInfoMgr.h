#pragma once
#include "SFML/Graphics.hpp"
#include "Singleton.h"
#include "repidcw.h"
#include <vector>
#include <iostream>

using namespace sf;

//struct GameData
//{
//	int BerryCount;
//	int DeathCount;
//	float TimeCount;
//	int tutorial;
//	int firstStage;
//
//};

class GameInfoMgr : public Singleton<GameInfoMgr>
{
private:
	std::vector<int> Index;
	std::vector<int> Berry;
	std::vector<int> Death;
	std::vector<float>playTime;
	std::vector<int> tutoClear;
	std::vector<int> firstClear;
	int saveDataIdx;

public:
	GameInfoMgr();
	void InitInfo();
	std::vector<int>getVecctorIndex();
	std::vector<int>getVectorBerry();
	std::vector<int>getVectorDeath();
	std::vector<float>getVectorTime();
	std::vector<int>getVectorTutoClear();
	std::vector<int>getVectorFirstClear();


};

