#pragma once

#include <SFML/Graphics.hpp>
// #include "../enemies/Enemy.h"
#include "../../commonFunctions/CommonFunctions.h"
#include "../../mainMenu/MainMenu.h"

class MainMenu;
class Enemy;

class Tower
{
    // sprite, damage, attackSpeed
    // getters, shootAnimation
private:
    sf::Sprite sprite;
    int cost;
    int damage[2];
    int shootSpeed;
    int range;

public:
    Tower(MainMenu &mainMenu, int code);
    sf::Sprite getSprite();
    int getCost();
    int getDamage();
    int getShootSpeed();
    int getRange();

    void setValues(std::vector<std::vector<int>> allStats, int code);

    void setSprite(sf::Sprite newSprite);
    void setCost(int newSost);
    void setDamage(int newDamageMin, int newDamageMax);
    void setShootSpeed(int newShootSpeed);
    void setRange(int newRange);

    void setPosition(int x, int y);
    sf::Vector2f getPosition();

    bool isEnemyInRange(Enemy *enemy);
    void shoot(Enemy *enemy);
};