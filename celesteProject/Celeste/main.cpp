#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Wall.h"
#include "Utils/InputMgr.h"

using namespace sf;


void CreateWalls(std::vector<Wall*>& walls, FloatRect bat, FloatRect bat2)
{
	for (auto v : walls)
	{
		delete v;
	}

	walls.clear();

	Wall* wallUp = new Wall(bat);
	walls.push_back(wallUp);
    Wall *wallRight = new Wall(bat2);
    walls.push_back(wallRight);
  
	/*Wall* wallDown = new Wall(bat.top + bat.height - offset, bat.left, bat.width, offset);
	walls.push_back(wallDown);
	Wall* wallLeft = new Wall(offset, bat.left, offset, bat.height - 2 * offset);
	walls.push_back(wallLeft);
	Wall* wallRight = new Wall(offset, bat.left + bat.width - offset, offset, bat.height - 2 * offset);
	walls.push_back(wallRight);*/
}

int main()
{
    RenderWindow window(VideoMode(1280, 720), "Celeste");
    
    Bat bat;
    Bat2 bat2;

    FloatRect bats = bat.GetBatRect();
    FloatRect bat2s = bat2.GetBatRect();
    
    std::vector <Wall*> walls;
    CreateWalls(walls, bats, bat2s);


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
      
        if (time.asSeconds() <= 1.f / 200.f)
        {
            InputMgr::Update(time.asSeconds());
           player.Update(time.asSeconds(), walls);
          // bat.Update(walls);
        }

        //DRAW
        window.clear();
        window.draw(bat.GetShape());
        window.draw(bat2.GetShape());
        player.Draw(window);
        window.display();       
    }
    return 0;
}