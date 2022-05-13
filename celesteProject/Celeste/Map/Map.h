#pragma once
#include"../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include "../Utils/repidcw.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>
#include "TileMap.h"
#include "../Obj.h"


class Map
{
private:

	std::vector<int> MapNumber;
	std::vector<int> MapXSize;
	std::vector<int> MapYSize;
	std::vector<std::string> OBJFilePath;
	std::vector<std::string> OBJSFilePath;

	std::vector<int> ColObjNum;
	std::vector<int> ColL;
	std::vector<int> ColT;
	std::vector<int> ColW;
	std::vector<int> ColH;

	std::vector<int> OBJnum;
	std::vector<std::string> ObjFilePath;
	std::vector<int> PosX;
	std::vector<int> PosY;

	std::vector<sf::RectangleShape*> blocks;
	std::vector<Obj*> Objs;

	Vector2i originPos;
	Vector2f worldPos;
	Vector2f currworldPos;
	
public:
	Map();
	void DrawMap(sf::RenderWindow& window);

	void LoadMap();
	void InputMap(int& windowMagnification, View& mainview, Time& dt, RenderWindow& window);

	std::vector<int> GetMapNumber();
	std::vector<int> GetMapXSize();
	std::vector<int> GetMapYSize();
	std::vector<sf::RectangleShape*> Getblocks();
	std::vector<Obj*> GetObjs();

	
};

