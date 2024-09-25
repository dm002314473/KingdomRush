#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include "../mainMenu/MainMenu.h"
#include "enemies/Enemy.h"
#include "enemies/Goblin.h"
#include "enemies/Giant.h"

class MainMenu;
class Enemy;

class EnemyFactory
{
public:
    EnemyFactory();
    Enemy *createEnemy(const std::string &type, MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints);

private:
    std::unordered_map<std::string, std::function<Enemy *(MainMenu &, std::vector<std::vector<int>> &)>> factoryMap;
};