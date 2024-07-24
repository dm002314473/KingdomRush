#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"
#include "enemies/Enemy.h"
#include "towers/Tower.h"

class Game;

class Level
{
private:
    std::vector<std::vector<Enemy *>> enemies;
    std::vector<sf::Sprite *> towerStands;
    std::vector<Tower *> towers;

public:
    void handleEvent(sf::Event &event, Game &game);
    void update();
    void render(sf::RenderWindow &window);
};