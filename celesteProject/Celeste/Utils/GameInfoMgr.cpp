#include "GameInfoMgr.h"

GameInfoMgr::GameInfoMgr()
{
	rapidcsv::Document gameInfo("dataCenter/gamedata.csv");

}

int GameInfoMgr::getBerry()
{
	return Berry[saveDataIdx];
}

int GameInfoMgr::getDeath()
{
	return Death[saveDataIdx];
}

float GameInfoMgr::getTime()
{
	return playTime[saveDataIdx];
}

int GameInfoMgr::getTutoClear()
{
	return tutoClear[saveDataIdx];
}

int GameInfoMgr::getFirstClear()
{
	return firstClear[saveDataIdx];
}
//void GameInfoMgr::addBerry()
//{
//	Berry[saveDataIdx]++;
//}


//값 넘겨주는건 싱글톤으로 해서 넘겨주고
// sstream 출력  딸기 ~~개 

//
//UIstringBerrys(int berry)
//{
//	ss << GameInfoMgr::GetInstance().getBerry();
//}

// GameInfoMgr::addBerry();
