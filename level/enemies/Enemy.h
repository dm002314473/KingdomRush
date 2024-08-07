#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include "../../mainMenu/MainMenu.h"
#include "../../commonFunctions/CommonFunctions.h"

class MainMenu;

class Enemy
{
private:
    int damage;
    int speedX;
    int speedY;
    int health;
    int magicArmor;
    int physicalArmor;
    int bounty;
    int attackSpeed;
    sf::Sprite sprite;

    std::vector<std::vector<int>> &waypoints;
    int currentWaypointIndex;
    bool outOfMap = false;

public:
    // moveAnimation
    Enemy(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints);
    void setHealth(int newHealth);
    void setDamage(int newDamage);
    void setSpeedX(int newSpeedX);
    void setSpeedY(int newSpeedY);
    void setMagicArmor(int newMagicArmor);
    void setPhysicalArmor(int newPhysicalArmor);
    void setBounty(int newBounty);
    void setAttackSpeed(int newAttackSpeed);
    void setSprite(sf::Sprite newSprite);
    void move();
    bool shouldEnemyTurn();
    bool isOutOfMap() { return outOfMap; }

    int getHealth();
    int getDamage();
    int getSpeedX();
    int getSpeedY();
    int getMagicArmor();
    int getPhysicalArmor();
    int getBounty();
    int getAttackSpeed();
    sf::Sprite getSprite();
};