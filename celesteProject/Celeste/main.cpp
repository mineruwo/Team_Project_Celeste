#include <SFML/Graphics.hpp>
#include "Utils/TextureHolder.h"
#include <string>
#include <iostream>
#include "Utils/InputMgr.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "Wall.h"


void CreateWalls(std::vector<Wall*>& walls, Map& mapdata);
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1366, 768), "Celeste");
    TextureHolder textureHolder;

    IntRect area;
    area.width = window.getSize().x;
    area.height = window.getSize().y;

    int windowMagnification = 2;
    View mainView(FloatRect(736, 256, area.width / windowMagnification, area.height / windowMagnification));

    View UiView(FloatRect(0, 0, window.getSize().x, window.getSize().y));

    Player player;
    bool isPlayerInit = false;

    Map map;
    Clock clock;

    int currMap = 0;

    std::vector <Wall*> walls;
    CreateWalls(walls, map);

    while (window.isOpen())
    {
        Event event;
        InputMgr::ClearInput();

        Time time = clock.restart();

        while (window.pollEvent(event))
        {
            InputMgr::ProcessInput(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        map.InputMap(windowMagnification, mainView, time, window);

        if (InputMgr::GetKeyDown(Keyboard::F3))
        {
            std::string mgr;
            mgr += "Map simulator";
            mgr += "_CurrMap Number is ";
            mgr += currMap;

            window.setTitle(mgr);

            area.width = map.GetMapXSize()[currMap];
            area.height = map.GetMapYSize()[currMap];
        }
        if (InputMgr::GetKeyDown(Keyboard::F2))
        {
            player.Init();
            isPlayerInit = true;
        }

        if (InputMgr::GetKeyDown(Keyboard::F5))
        {
            /* for (auto it : walls)
             {
                 delete it;
             }

             for (auto it : map.Getblocks())
             {
                 delete it;
             }
             walls.clear();
             map.Getblocks().clear();*/
        }

        //UPDATE
        if (isPlayerInit && time.asSeconds() <= 1.f / 200.f)
        {
            InputMgr::Update(time.asSeconds());
            player.Update(time.asSeconds(), walls);
        }
        CreateWalls(walls, map);

        //DRAW
        window.clear();
        window.setView(mainView);

        if (isPlayerInit && time.asSeconds() <= 1.f / 200.f)
        {
            window.draw(player.GetSprite());
        }
        for (auto it : walls)
        {
            it->DrawWall(window);
        }
        map.DrawMap(window);

        //window.draw(bat.GetShape());
        //window.draw(bat2.GetShape());
        player.Draw(window);
        window.display();
    }
    return 0;
}

void CreateWalls(std::vector<Wall*>& walls, Map& mapdata)
{
    for (auto v : walls)
    {
        delete v;
    }

    walls.clear();

    int idx = 0;

    while (true)
    {

        if (idx == mapdata.Getblocks().size())
        {
            break;
        }

        Wall* tile = new Wall(mapdata.Getblocks()[idx]->getGlobalBounds());
        walls.push_back(tile);

        idx++;

    }

}