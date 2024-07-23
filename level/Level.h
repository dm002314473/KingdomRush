#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"

class Game;

class Level
{
public:
    void handleEvent(sf::Event &event, Game &game);
    void update();
    void render(sf::RenderWindow &window);
};