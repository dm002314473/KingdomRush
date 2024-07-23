#include <iostream>
#include "Game.h"
#include "Level.h"

int main(void)
{
    std::cout << "Soso";

    Game game("mainMenu/mainMenu.txt");
    game.run();

    return 0;
}