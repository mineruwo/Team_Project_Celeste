#include "TileMap.h"
#include <iostream>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // transform ����
    states.transform *= getTransform();

    // tileset �ؽ��� ����
    states.texture = &m_tileset;

    // vertex array �׸���
    target.draw(m_vertices, states);
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height, Vector2f pos)
{
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // vertex array�� ����� �� level�� ����� �°� ����
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    int idx = 0;
    // tile���� �ϳ��� quad�� vertex array ä���
    for (unsigned int i = 0; i < width; ++i) 
    {
        for (unsigned int j = 0; j < height; ++j)
        {
          

            // ���� tile �� ��������
            int tileNumber = tiles[i + j * width];

            // tileset �ؽ��Ŀ��� �� ��ġ Ž��
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
         

            // ���� tile�� quad ������ ȹ��
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // 4���� �ڳ� ����
            quad[0].position = sf::Vector2f(i * tileSize.x + pos.x, j * tileSize.y + pos.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x + pos.x, j * tileSize.y + pos.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x + pos.x, (j + 1) * tileSize.y + pos.y);
            quad[3].position = sf::Vector2f(i * tileSize.x + pos.x, (j + 1) * tileSize.y + pos.y);

            // �ؽ��� ��ǥ 4�� ����
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




