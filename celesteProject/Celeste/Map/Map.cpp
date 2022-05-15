#include "Map.h"
#define TILEDRAWSIZE 16;


Map::Map()
{
    rapidcsv::Document mapData("data_tables/Maps/Mapdata.csv");

    MapNumber = mapData.GetColumn<int>("MapNumber");
    MapXSize = mapData.GetColumn<int>("MapXSize");
    MapYSize = mapData.GetColumn<int>("MapYSize");
    OBJFilePath = mapData.GetColumn<std::string>("OBJFilePath");
    OBJSFilePath = mapData.GetColumn<std::string>("OBJSFilePath");
    TileDataFilePath = mapData.GetColumn<std::string>("TileFilePath");


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

    for (auto it : TileDataFilePath)
    {
        rapidcsv::Document tileData(it);
        tileNum = tileData.GetColumn<int>("tilenum");
        TileFilePath = tileData.GetColumn<std::string>("TileFilePath");
        TilePosX = tileData.GetColumn<int>("PosX");
        TilePosY = tileData.GetColumn<int>("PosY");
        coordl = tileData.GetColumn<int>("coordl");
        coordt = tileData.GetColumn<int>("coordt");
        id = tileData.GetColumn<int>("id");
    }

}

void Map::InputMap(int& windowMagnification, View& mainview, Time& dt)
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
    float offset = 32.f;

    if (InputMgr::GetKeyDown(Keyboard::A))
    {

        mainview.move(-1 * offset, 0.f);

    }
    if (InputMgr::GetKeyDown(Keyboard::D))
    {
        mainview.move(offset, 0.f);
    }

    if (InputMgr::GetKeyDown(Keyboard::S))
    {
        mainview.move(0.f, offset);
    }
    if (InputMgr::GetKeyDown(Keyboard::W))
    {
        mainview.move(0.f, -1 * offset);
    }

    if (InputMgr::GetKeyDown(Keyboard::BackSpace))
    {

        if (!blocks.empty())
        {
            blocks.pop_back();

        }
    }
    if (InputMgr::GetKeyDown(Keyboard::Delete))
    {

        if (!Objs.empty())
        {
            Objs.pop_back();

        }
    }
    if (InputMgr::GetKeyDown(Keyboard::Space))
    {
        if (!tiles.empty())
        {
            tiles.pop_back();
        }
    }
}

void Map::DrawMap(sf::RenderWindow& window)
{

    if (isDrag)
    {
        window.draw(*currDrag);
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

    idx = 0;
    for (auto it : tileNum)
    {
        Tile* createTile = new Tile;

        createTile->SetFile(TileFilePath[idx]);
        createTile->SetPosition(Vector2f(TilePosX[idx], TilePosY[idx]));
        createTile->SetCoord(IntRect(coordl[idx], coordt[idx], 8, 8));
        createTile->SetID(id[idx]);

        tiles.push_back(createTile);

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

std::vector<Tile*> Map::GetTiles()
{
    return tiles;
}

