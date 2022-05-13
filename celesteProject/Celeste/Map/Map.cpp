#include "Map.h"

Map::Map()
{
    rapidcsv::Document mapData("data_tables/Maps/Mapdata.csv");

    MapNumber = mapData.GetColumn<int>("MapNumber");
    MapXSize = mapData.GetColumn<int>("MapXSize");
    MapYSize = mapData.GetColumn<int>("MapYSize");
    OBJFilePath = mapData.GetColumn<std::string>("OBJFilePath");
    OBJSFilePath = mapData.GetColumn< std::string>("OBJSFilePath");

    for (auto it : OBJFilePath)
    {
        rapidcsv::Document objData(it);
        ColObjNum = objData.GetColumn<int>("ColObjNum");
        ColL = objData.GetColumn<int>("ColL");
        ColT = objData.GetColumn<int>("ColT");
        ColW = objData.GetColumn<int>("ColW");
        ColH = objData.GetColumn<int>("ColH");
    }

    for (auto it : OBJSFilePath)
    {
        rapidcsv::Document objsData(it);
        OBJnum = objsData.GetColumn<int>("OBJnum");
        ObjFilePath = objsData.GetColumn<std::string>("ObjFilePath");
        PosX = objsData.GetColumn<int>("PosX");
        PosY = objsData.GetColumn<int>("PosY");
    }
    
}

void Map::InputMap(int& windowMagnification, View& mainview, Time& dt, RenderWindow& window)
{


    if (InputMgr::GetKeyDown(Keyboard::PageUp))
    {
        windowMagnification++;

        if (windowMagnification > 7)
        {
            windowMagnification = 7;
        }

        mainview.setSize(1366 / windowMagnification, 768 / windowMagnification);
    }
    if (InputMgr::GetKeyDown(Keyboard::PageDown))
    {
        windowMagnification--;

        if (windowMagnification < 1)
        {
            windowMagnification = 1;
        }

        mainview.setSize(1366 / windowMagnification, 768 / windowMagnification);

    }
    float offset = 300.f;

    if (InputMgr::GetKey(Keyboard::A))
    {

        mainview.move(-1 * offset * dt.asSeconds(), 0.f);

    }
    if (InputMgr::GetKey(Keyboard::D))
    {
        mainview.move(offset * dt.asSeconds(), 0.f);
    }

    if (InputMgr::GetKey(Keyboard::S))
    {
        mainview.move(0.f, offset * dt.asSeconds());
    }
    if (InputMgr::GetKey(Keyboard::W))
    {
        mainview.move(0.f, -1 * offset * dt.asSeconds());
    }

    
}

void Map::DrawMap(sf::RenderWindow& window)
{
 
    for (auto it : Objs)
    {
        window.draw(it->GetSprite());
    }
 
}

void Map::LoadMap()
{
    int idx = 0;
    for (auto it : ColObjNum)
    {
        RectangleShape* createBlock = new RectangleShape;

        createBlock->setPosition(ColL[idx], ColT[idx]);
        createBlock->setSize(Vector2f(ColW[idx], ColH[idx]));

        blocks.push_back(createBlock);

        idx++;
    }

    idx = 0;
    for (auto it : OBJnum)
    {
        Obj* creatobj = new Obj;

        creatobj->SetFile(ObjFilePath[idx]);
        creatobj->SetPosition(Vector2f(PosX[idx], PosY[idx]));

        Objs.push_back(creatobj);

        idx++;
    }
   
}

std::vector<int> Map::GetMapNumber()
{
    return MapNumber;
}

std::vector<int> Map::GetMapXSize()
{
    return MapXSize;
}

std::vector<int> Map::GetMapYSize()
{
    return MapYSize;
}

std::vector<sf::RectangleShape*> Map::Getblocks()
{
    return blocks;
}

std::vector<Obj*> Map::GetObjs()
{
    return Objs;
}

