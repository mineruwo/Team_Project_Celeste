#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Bat.h"
#include "Utils/InputMgr.h"

using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1280, 720), "Celeste");
    
    Bat bat(0, 720 * 0.5f);

    InputMgr::Init();
    Player player;
    player.Init();

    Clock clock;
    while (window.isOpen())
    {
        Time time = clock.restart();
        Event event;
        InputMgr::ClearInput();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::ProcessInput(event);
        }

        //UPDATE
        InputMgr::Update(time.asSeconds());
        player.Update(time.asSeconds());
        //bat.Update();

        //DRAW
        window.clear();
        window.draw(bat.GetShape());
        player.Draw(window);
        window.display();       
    }
    return 0;
}