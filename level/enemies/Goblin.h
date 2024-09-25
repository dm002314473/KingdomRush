#pragma once

#include "Enemy.h"

class Goblin : public Enemy
{
public:
    Goblin(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints);
};
