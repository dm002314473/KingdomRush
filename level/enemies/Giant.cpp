#include "Giant.h"
#include "Enemy.h"

Giant::Giant(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints)
    : Enemy(mainMenu, waypoints, GIANT)
{
    std::cout << "Giant KONST" << std::endl;
}
