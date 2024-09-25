#pragma once

#include "Enemy.h"

class Giant : public Enemy
{
public:
    Giant(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints);
};
