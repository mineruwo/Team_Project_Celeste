#pragma once
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../Utils/repidcw.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>
#include "Tile.h"
#include "Obj.h"

#define TilePath "Graphics/tilesets"
#define ObjPath "Graphics"

class Map
{
private:

	std::vector<int> MapNumber;
	std::vector<int> MapXSize;
	std::vector<int> MapYSize;
	std::vector<std::string> OBJFilePath;
	std::vector<std::string> OBJSFilePath;
	std::vector<std::string> TileDataFilePath;

	std::vector<int> ColObjNum;
	std::vector<int> ColL;
	std::vector<int> ColT;
	std::vector<int> ColW;
	std::vector<int> ColH;

	std::vector<int> OBJnum;
	std::vector<std::string> ObjFilePath;
	std::vector<int> PosX;
	std::vector<int> PosY;

	std::vector<int> tileNum;
	std::vector<std::string> TileFilePath;
	std::vector<int> TilePosX;
	std::vector<int> TilePosY;
	std::vector<int> coordl;
	std::vector<int> coordt;
	std::vector<int> id;
	std::vector<int> tileset;

	std::vector<sf::RectangleShape*> blocks;//rect
	std::vector<Obj*> Objs;//obj
	std::vector <Tile*> tiles;//tile

	Vector2i originPos;
	Vector2f worldPos;
	Vector2f currworldPos;
	bool isDrag = false;

	RectangleShape* currDrag;

public:
	Map();
	void InputMap(int& windowMagnification, View& mainview, Time& dt);
	
	void DrawMap(sf::RenderWindow& window);

	void LoadMap();


	std::vector<int> GetMapNumber();
	std::vector<int> GetMapXSize();
	std::vector<int> GetMapYSize();
	std::vector<sf::RectangleShape*> Getblocks();
	std::vector<Obj*> GetObjs();
	std::vector<Tile*> GetTiles();


};

