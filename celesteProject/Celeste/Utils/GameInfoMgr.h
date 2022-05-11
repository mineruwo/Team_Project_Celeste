#pragma once
#include "SFML/Graphics.hpp"
#include "Singleton.h"
#include "repidcw.h"
#include <vector>
#include <iostream>


using namespace sf;

class GameInfoMgr : public Singleton<GameInfoMgr>
{
private:
	std::vector<int> Berry ;
	std::vector<int> Death;
	std::vector<float>playTime;
	std::vector<int> tutoClear;
	std::vector<int> firstClear;

	int saveDataIdx;

public:
	GameInfoMgr();
	int getBerry();
	int getDeath();
	float getTime();
	int getTutoClear();
	int getFirstClear();
	






};

