#include <iostream>
#include "Game.h"

int main(void)
{
    std::cout << "Soso";

    Game game("mainMenu/mainMenu.txt");
    game.run();

    return 0;
}