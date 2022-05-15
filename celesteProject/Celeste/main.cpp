#include <SFML/Graphics.hpp>
#include "Utils/TextureHolder.h"
#include <string>
#include <iostream>
#include "Utils/InputMgr.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "Wall.h"
#include "Object/Berry.h"
#include "Object/Thorny.h"


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

    View backView = window.getDefaultView();

    Player player;
    bool isPlayerInit = false;


    View mainView(FloatRect(0, 0, area.width / windowMagnification, area.height / windowMagnification));

    Sprite backGround;
    backGround.setTexture(TextureHolder::GetTexture("graphics/Background.png"));
    backGround.setScale(Vector2f(2.0f, 2.0f));

    Berry berry;
    berry.Init();

    Thorny thorny;
    thorny.Init();

    Map map;
    Clock clock;

    map.LoadMap();
    int currMap = 0;

    std::vector <Wall*> walls;
    CreateWalls(walls, map);

    while (window.isOpen())
    {
        Time elapseed = clock.getElapsedTime();
        if (elapseed.asSeconds() < 1.f / 60.f)
            continue;

        Time time = clock.restart();
        Event event;
        InputMgr::ClearInput();

        while (window.pollEvent(event))
        {
            InputMgr::ProcessInput(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        map.InputMap(windowMagnification, mainView, time);

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

        InputMgr::Update(time.asSeconds());
        player.Update(time.asSeconds(), walls);
        mainView.setCenter(player.GetPosition().x, player.GetPosition().y);
        berry.Update(player, time.asSeconds());
        thorny.Update(player);

        //DRAW
        window.clear();
        window.setView(backView);
        window.draw(backGround);

        window.setView(mainView);

        if (isPlayerInit && time.asSeconds() <= 1.f / 120.f)
        {

            window.draw(player.GetSprite());
        }
        for (auto it : walls)
        {
            it->DrawWall(window);
        }
        for (auto it : map.GetObjs())
        {
            window.draw(it->GetSprite());
        }
        for (auto it : walls)
        {
            it->DrawWall(window);
        }

        for (auto it : map.GetTiles())
        {
            window.draw(it->GetSprite());
        }
        map.DrawMap(window);
        player.Draw(window);
        berry.Draw(window);
        thorny.Draw(window);
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