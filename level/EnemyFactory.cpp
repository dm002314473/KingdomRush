#include "EnemyFactory.h"

EnemyFactory::EnemyFactory()
{
    factoryMap["goblin"] = [](MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints) -> Enemy *
    { return new Goblin(mainMenu, waypoints); };
    factoryMap["giant"] = [](MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints) -> Enemy *
    { return new Giant(mainMenu, waypoints); };
}

Enemy *EnemyFactory::createEnemy(const std::string &type, MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints)
{
    std::cout << "CREATE ENEMY" << std::endl;
    auto it = factoryMap.find(type);
    if (it != factoryMap.end())
        return it->second(mainMenu, waypoints);
    return nullptr;
}