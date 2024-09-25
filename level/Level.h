#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"
#include "enemies/Enemy.h"
#include "towers/Tower.h"
#include "../mainMenu/MainMenu.h"
#include "../commonFunctions/CommonFunctions.h"
#include "EnemyFactory.h"

class Game;
class MainMenu;
class Enemy;
class Tower;

class Level
{
private:
    sf::Sprite levelBackground;
    sf::Sprite menuStand;
    std::vector<Enemy *> enemies;
    std::vector<sf::Sprite *> towerStands;
    std::vector<Tower *> towers;

    std::vector<sf::Sprite *> buttons;
    MainMenu &mainMenu;

    std::vector<std::vector<int>> waypoints;
    std::vector<std::vector<int>> towerStandsPositions;
    std::vector<int> heroStandPosition;
    int wave = 0;

    bool isLevelPaused;
    bool isMenuStandOpen = false;

public:
    Level(int levelIndex, MainMenu &mainMenu);
    sf::Sprite getSprite();

    void handleEvent(sf::Vector2i &mousePos, Game &game, bool &exitLevel);
    void update();
    void render(sf::RenderWindow &window);
    void readingLevelData(std::string &levelTxtFile);
    void settingTowerStands();

    void startNewWave(int waveIndex);

    void handleMenuClickEvent(sf::Vector2i &mousePos, sf::Sprite &menuStand);

    void createTower(int code);
};