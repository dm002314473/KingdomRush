#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"
#include "enemies/Enemy.h"
#include "towers/Tower.h"
#include "../mainMenu/MainMenu.h"

class Game;
class MainMenu;
class Enemy;
class Tower;

class Level
{
private:
    sf::Sprite levelBackground;
    std::vector<Enemy *> enemies;
    std::vector<sf::Sprite *> towerStands;
    std::vector<Tower *> towers;
    sf::Sprite newWaveButton;
    MainMenu &mainMenu;

public:
    Level(int levelIndex, MainMenu &mainMenu);
    sf::Sprite getSprite();

    void handleEvent(sf::Vector2i &mousePos, Game &game);
    void update();
    void render(sf::RenderWindow &window);

    void startNewWave(int waveIndex);
};