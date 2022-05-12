#include "GameInfoMgr.h"

GameInfoMgr::GameInfoMgr()
{
	rapidcsv::Document gameInfo("data_tables/gamedata.csv");

	Index = gameInfo.GetColumn<int>("Index");
	Berry = gameInfo.GetColumn<int>("Berry");
	Death = gameInfo.GetColumn<int>("Death");
	playTime = gameInfo.GetColumn<float>("PlayTime");
	tutoClear = gameInfo.GetColumn<int>("Tutorial");
	firstClear = gameInfo.GetColumn<int>("First");

}

void GameInfoMgr::InitInfo()
{


}

std::vector<int> GameInfoMgr::getVecctorIndex()
{
	return Index;
}

std::vector<int> GameInfoMgr::getVectorBerry()
{
	return Berry;
}

std::vector<int> GameInfoMgr::getVectorDeath()
{
	return Death;
}

std::vector<float> GameInfoMgr::getVectorTime()
{
	return playTime;
}

std::vector<int> GameInfoMgr::getVectorTutoClear()
{
	return tutoClear;
}

std::vector<int> GameInfoMgr::getVectorFirstClear()
{
	return firstClear;
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
