#include <iostream>
#include "Game.hpp"



int main()
{
    Game game;
    game.render();
    //Game loop
    while (game.is_window_open())
    {
        game.update();
    }


    return 0;
}

