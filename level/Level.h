#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"
#include "enemies/Enemy.h"
#include "towers/Tower.h"
#include "../mainMenu/MainMenu.h"

class Game;
class MainMenu;

class Level
{
private:
    sf::Texture backgroundTexture;
    sf::Sprite levelBackground;
    std::vector<Enemy *> enemies;
    std::vector<sf::Sprite *> towerStands;
    std::vector<Tower *> towers;

public:
    Level(int levelIndex, MainMenu &mainMenu);
    sf::Sprite getSprite();

    void handleEvent(sf::Event &event, Game &game);
    void update();
    void render(sf::RenderWindow &window);
};