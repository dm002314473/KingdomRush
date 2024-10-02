#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
// #include "../enemies/Enemy.h"
#include "../../commonFunctions/CommonFunctions.h"
#include "../../mainMenu/MainMenu.h"
#include "../Level.h"

class MainMenu;
class Enemy;

class Tower
{
    // sprite, damage, attackSpeed
    // getters, shootAnimation
private:
    sf::Sprite sprite;
    sf::Sprite towerUpgradeMenu;
    int cost;
    int damage[2];
    int shootSpeed;
    int range;
    int code;
    int nextLevelCost;
    int apsoluteCost;
    sf::CircleShape shootRadius;

    float attackCooldown;
    sf::Time timeSinceLastShot = sf::Time::Zero;
    Enemy *currentTarget;
    bool hasTarget;

public:
    Tower(MainMenu &mainMenu, int code);
    sf::Sprite &getSprite();
    int getCost();
    int getDamage();
    int getShootSpeed();
    int getRange();
    int getCode();
    int getNextLevelCost();
    int getApsoluteCost();

    sf::Time getElapsedTime();
    void setElapsedTime(sf::Time time);

    sf::Time getTimeSinceLastTowerAttack();
    void setTimeSinceLastTowerAttack(sf::Time time);

    void setValues(std::vector<std::vector<int>> allStats, int code);

    void setSprite(sf::Sprite newSprite);
    void setCost(int newCost);
    void setDamage(int newDamageMin, int newDamageMax);
    void setShootSpeed(int newShootSpeed);
    void setRange(int newRange);
    void setCode(int newCode);
    void setNextLevelCost(int newNextLevelCost);
    void setApsoluteCost(int newApsoluteCost);

    void setPosition(int x, int y);
    sf::Vector2f getPosition();

    bool isEnemyInRange(Enemy *enemy);
    double calculateDistance(Enemy *enemy, Tower *tower);
    void shoot(std::vector<Enemy *> &enemies, sf::Time deltaTime);

    bool isClicked(sf::Vector2i &mousePos);
    void handleClick(MainMenu &mainMenu, sf::Vector2i &mousePos);

    sf::CircleShape &getShootRadius();
    void setShootingRadius(float radius, sf::Vector2f radiusPosition, float transparency);

    bool getHasTarget();
    void setHasTarget(bool set);
    Enemy *getCurrentEnemy();
    void setCurrentEnemy(Enemy *enemy);
};