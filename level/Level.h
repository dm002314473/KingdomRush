#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include "../Game.h"
#include "enemies/Enemy.h"
#include "towers/Tower.h"
#include "heroes/Hero.h"
#include "waves/Wave.h"
#include "../mainMenu/MainMenu.h"
#include "../commonFunctions/CommonFunctions.h"

class Game;
class MainMenu;
class Enemy;
class Tower;
class Hero;
class Wave;
class Projectile;

class Level
{
private:
    sf::Texture *levelBackgroundTexture;
    sf::Sprite levelBackground;
    sf::Sprite menuStand;
    sf::Sprite towerUpgrade;
    sf::Sprite towerUpgradeSplit;
    sf::Sprite towerAbilityUpgrade;
    std::vector<Enemy *> enemies;
    std::vector<sf::Sprite *> towerStands;
    std::vector<Tower *> towers;
    std::vector<Projectile *> projectiles;
    Hero *hero;
    std::vector<sf::Shape *> holyLands;

    std::vector<sf::Sprite *> buttons;
    MainMenu &mainMenu;

    std::vector<std::vector<int>> waypoints;
    std::vector<std::vector<int>> holyLandPoints;
    std::vector<std::vector<int>> towerStandsPositions;
    std::vector<int> heroStandPosition;
    int wave = 0;
    int money = 0;

    bool isLevelPaused;
    bool isMenuStandOpen = false;
    bool isTowerUpgradeOpen = false;
    bool isTowerUpgradeSplitOpen = false;
    bool isAbilityUpgradeOpen = false;
    sf::Text moneyText;
    sf::RectangleShape moneyBox;
    sf::Font font;
    std::stringstream ss;

    sf::CircleShape radius;
    bool isRadiusVisible;
    Tower *selectedTower = nullptr;

    bool isHeroSelected = false;
    bool isHeroMoving = false;
    sf::Vector2i targetPos;
    sf::Clock clock;
    sf::Clock clockTowerShoot;
    sf::Clock clockMoving;
    sf::Clock clockHeal;
    sf::Time heroAttackInterval;
    sf::Time enemyAttackInterval;
    sf::Time holyLandHealInterval;
    sf::Time timeSinceLastHeroAttack = sf::Time::Zero;
    sf::Time timeSinceLastEnemyAttack = sf::Time::Zero;
    sf::Time timeSinceLastHeroHeal = sf::Time::Zero;
    sf::Time timeSinceLastHolyLandHeal = sf::Time::Zero;
    sf::Time heroHealInterval = sf::milliseconds(1000);

    sf::Time timeSinceLastTowerAttack = sf::Time::Zero;

    sf::Time towerAttackInterval;
    Enemy *fightingEnemy = nullptr;
    int t = 0;
    std::vector<Wave> levelWaves;

    sf::Image image;
    std::vector<sf::Color> colors;
    sf::Vector2u imageSize;

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
    void handleUpgradeTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgrade, Tower *tower);
    void handleUpgradeSplitTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgradeSplit, Tower *tower);
    void handleAbilityUpgradeTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerAbilityUpgrade, Tower *tower);

    void createTower(int code, sf::Sprite &stand);
    void upgradeTower(Tower *tower, int code);
    void deleteTower(Tower *towerToDelete);

    void createHero(int code);

    void setMoney(int newMoney);
    int getMoney();
    void updateMoney(int price);

    sf::Vector2f getHeroStandPosition();

    void closeAllUpgradeMenus();
    void openTowerUpgradeMenu(Tower *tower);
    void openTowerUpgradeSplitMenu(Tower *tower);
    void openAbilityUpgradeMenu(Tower *tower);

    void performBattle(Hero *&hero, Enemy *&fightingEnemy, std::vector<Enemy *> &enemies, float dtm);

    void holyLandHeal(Hero *&hero);
    void settingHolyLand();

    void heroHeal();
};