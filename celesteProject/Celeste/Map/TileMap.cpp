#include "TileMap.h"
#include <iostream>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // transform 적용
    states.transform *= getTransform();

    // tileset 텍스쳐 적용
    states.texture = &m_tileset;

    // vertex array 그리기
    target.draw(m_vertices, states);
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height, Vector2f pos)
{
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // vertex array의 사이즈를 그 level의 사이즈에 맞게 조정
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    int idx = 0;
    // tile마다 하나의 quad로 vertex array 채우기
    for (unsigned int i = 0; i < width; ++i) 
    {
        for (unsigned int j = 0; j < height; ++j)
        {
          

            // 현재 tile 수 가져오기
            int tileNumber = tiles[i + j * width];

            // tileset 텍스쳐에서 그 위치 탐색
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
         

            // 현재 tile의 quad 포인터 획득
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // 4개의 코너 정의
            quad[0].position = sf::Vector2f(i * tileSize.x + pos.x, j * tileSize.y + pos.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x + pos.x, j * tileSize.y + pos.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x + pos.x, (j + 1) * tileSize.y + pos.y);
            quad[3].position = sf::Vector2f(i * tileSize.x + pos.x, (j + 1) * tileSize.y + pos.y);

            // 텍스쳐 좌표 4개 정의
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

            std::cout << "set [" << i << "]" << "[" << j << "]" << std::endl;
            idx++;
        }
    }
        
    return true;
}

VertexArray TileMap::GetVertexArray()
{
    return m_vertices;
}




