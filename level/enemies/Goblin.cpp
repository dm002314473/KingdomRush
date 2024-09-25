#include "Goblin.h"
#include "Enemy.h"

Goblin::Goblin(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints)
    : Enemy(mainMenu, waypoints, BOLT)
{
    std::cout << "GOBLIN KONST" << std::endl;
}
