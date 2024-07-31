#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"
#include "enemies/Enemy.h"
#include "towers/Tower.h"
#include "../mainMenu/MainMenu.h"
#include "../commonFunctions/CommonFunctions.h"

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
    sf::Sprite pauseButton;
    sf::Sprite exitButton;
    sf::Sprite continueButton;
    sf::Sprite forPauseButton;
    MainMenu &mainMenu;

    std::vector<std::vector<int>> waypoints;
    std::vector<std::vector<int>> towerStandsPositions;
    std::vector<int> heroStandPosition;
    int wave = 0;

    bool isLevelPaused;

public:
    Level(int levelIndex, MainMenu &mainMenu);
    sf::Sprite getSprite();

    void handleEvent(sf::Vector2i &mousePos, Game &game, bool &exitLevel);
    void update();
    void render(sf::RenderWindow &window);
    void readingLevelData(std::string &levelTxtFile);

    void startNewWave(int waveIndex);
};