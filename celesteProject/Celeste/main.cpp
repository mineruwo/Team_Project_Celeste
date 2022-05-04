#include <SFML/Graphics.hpp>
#include "Framework/Framework.h"

int main()
{
    Framework mainLoop;
    mainLoop.init();

    while (true)
    {
        mainLoop.Update();
        mainLoop.Draw();
    }

}