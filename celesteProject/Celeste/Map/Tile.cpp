#include "Tile.h"

Tile::Tile()
{
	
}

Tile::Tile(std::string FilePath, int id, IntRect coord)
{
	tile.setTexture(TextureHolder::GetTexture(FilePath));
	tile.setScale(Vector2f(2, 2));
	tile.setTextureRect(coord);
	this->coord.left = tile.getTextureRect().left;
	this->coord.top = tile.getTextureRect().top;
	this->id = id;
	setFilePath = FilePath;

}


void Tile::Draw(RenderWindow& window)
{
	window.draw(tile);
}

void Tile::SetFile(std::string FilePath)
{
	setFilePath = FilePath;
	tile.setTexture(TextureHolder::GetTexture(FilePath));
	tile.setScale(Vector2f(2, 2));
}

void Tile::SetPosition(Vector2f pos)
{
	tile.setPosition(Vector2f(pos));
}

std::string Tile::GetFilePath()
{
	return setFilePath;
}

Sprite Tile::GetSprite()
{
	return tile;
}

void Tile::SetActive(bool isActive)
{
	this->isActive = isActive;
}

bool Tile::GetActive()
{
	return isActive;
}

int Tile::GetID()
{
	return id;
}

void Tile::SetID(int id)
{
	this->id = id;
}

void Tile::CopyTile(Tile copy)
{
	tile = copy.GetSprite();
	setFilePath = copy.GetFilePath();
	info = copy.GetTilesets();
	isActive = copy.GetActive();
	id = copy.GetID();

}

void Tile::SetTileSetsInfo(int idx)
{
	info = tilesets(idx);
}

tilesets Tile::GetTilesets()
{
	return info;
}

void Tile::SetCoord(IntRect coord)
{
	this->coord = coord;
	tile.setTextureRect(coord);

}

IntRect Tile::GetCoord()
{
	return tile.getTextureRect();
}


