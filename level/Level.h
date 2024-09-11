#pragma once

#include <SFML/Graphics.hpp>
#include <string>
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
    sf::Sprite menuStand;
    sf::Sprite towerUpgrade;
    sf::Sprite towerUpgradeSplit;
    std::vector<Enemy *> enemies;
    std::vector<sf::Sprite *> towerStands;
    std::vector<Tower *> towers;

    std::vector<sf::Sprite *> buttons;
    MainMenu &mainMenu;

    std::vector<std::vector<int>> waypoints;
    std::vector<std::vector<int>> towerStandsPositions;
    std::vector<int> heroStandPosition;
    int wave = 0;
    int money = 0;

    bool isLevelPaused;
    bool isMenuStandOpen = false;
    sf::Text moneyText;
    sf::RectangleShape moneyBox;
    sf::Font font;
    std::stringstream ss;

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
    void handleUpgradeTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgrade, Tower* tower);
    void handleUpgradeSplitTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgradeSplit, Tower* tower);

    void createTower(int code, sf::Sprite &stand);
    void upgradeTower(Tower* tower, int code);
    void deleteTower();

    void setMoney(int newMoney);
    int getMoney();

    void updateMoney(int price);
};