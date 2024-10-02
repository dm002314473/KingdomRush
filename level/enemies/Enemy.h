#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include "../../mainMenu/MainMenu.h"
#include "../../commonFunctions/CommonFunctions.h"

class MainMenu;

class Hero;

class Enemy
{
private:
    int damage[2];
    int speedX;
    int speedY;
    int health;
    int magicArmor;
    int physicalArmor;
    int bounty;
    int attackSpeed;
    int liveTaking;
    sf::Sprite sprite;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> walkingTextures;

    std::vector<std::vector<int>> &waypoints;
    int currentWaypointIndex;
    bool outOfMap = false;
    bool isEnemyFighting = false;
    bool isEnemyAlive = true;

    sf::Clock animationClock;
    int currentFrame = 0;
    bool isAnimating = false;
    sf::Time frameDuration = sf::milliseconds(1500 / 6.);
    sf::Time animationDuration = sf::milliseconds(1500);

public:
    // moveAnimation
    Enemy(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints, std::pair<int, int> pair);
    void setValues(std::vector<std::vector<int>> allStats, int code);
    void setHealth(int newHealth);
    void setDamage(int newDamage1, int newDamage2);
    void setSpeedX(int newSpeedX);
    void setSpeedY(int newSpeedY);
    void setMagicArmor(int newMagicArmor);
    void setPhysicalArmor(int newPhysicalArmor);
    void setBounty(int newBounty);
    void setAttackSpeed(int newAttackSpeed);
    void setSprite(sf::Sprite newSprite);
    void setLiveTaking(int newLiveTaking);
    void move();
    void stop();
    bool shouldEnemyTurn();
    bool isOutOfMap() { return outOfMap; }

    void setIsEnemyFighting(bool condition);
    bool getIsEnemyFighting();

    int getHealth();
    int getDamage();
    int getSpeedX();
    int getSpeedY();
    int getMagicArmor();
    int getPhysicalArmor();
    int getBounty();
    int getAttackSpeed();
    sf::Sprite getSprite();
    int getLiveTaking();

    void setIsEnemyAlive(bool condition);
    bool getIsEnemyAlive();
    void fighting(Hero *hero);

    void performAttackAnimation();
    void loadEnemyTextures(MainMenu &mainMenu, int code, std::vector<sf::Texture> &textures);

    void performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration);
    std::vector<sf::Texture> &getAttackTexture();
    std::vector<sf::Texture> &getWalkTexture();
};