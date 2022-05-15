#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/TextureHolder.h"


using namespace sf;

enum class tilesets
{
	bgDirt,
	bgBrick,
	bgSnow,
	cement,
	dirt,
	girder,
	snow,
	count
};

class Tile
{
private:
	Sprite tile;
	tilesets info;
	std::string setFilePath;
	IntRect coord;
	bool isActive = false;
	int id;
	
public:
	Tile();
	Tile(std::string FilePath, int id, IntRect coord);

	void Draw(RenderWindow& window);

	void SetFile(std::string FilePath);
	void SetPosition(Vector2f pos);

	std::string GetFilePath();
	Sprite GetSprite();

	void SetActive(bool isActive);
	bool GetActive();

	int GetID();
	void SetID(int id);
	void CopyTile(Tile copy);

	void SetTileSetsInfo(int idx);
	tilesets GetTilesets();

	void SetCoord(IntRect coord);
	IntRect GetCoord();


};

