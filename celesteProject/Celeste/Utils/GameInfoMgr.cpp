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


//�� �Ѱ��ִ°� �̱������� �ؼ� �Ѱ��ְ�
// sstream ���  ���� ~~�� 

//
//UIstringBerrys(int berry)
//{
//	ss << GameInfoMgr::GetInstance().getBerry();
//}

// GameInfoMgr::addBerry();
