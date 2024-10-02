#pragma once

#include <iostream>
#include "../../mainMenu/MainMenu.h"
#include "../../commonFunctions/CommonFunctions.h"

class Wave
{
private:
    std::vector<std::pair<int, int>> wave;

public:
    Wave();
    void pushEnemyToWave(int nameCode, int spawnTime);
    int getSize();
    std::pair<int, int> getEnemy(int index);
    void erase();
};