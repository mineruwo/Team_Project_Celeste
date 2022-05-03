#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Utils/InputMgr.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Celeste");
    InputMgr::Init();
    Player player;
    player.Init();

    RectangleShape shape(Vector2f(600, 50));
    shape.setFillColor(Color(100, 250, 50));

    shape.setPosition(0, 100);
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

        //DRAW
        window.clear();
        window.draw(shape);
        player.Draw(window);
        window.display();       
    }
    return 0;
}