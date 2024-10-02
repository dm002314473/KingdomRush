#pragma once

#include <SFML/Graphics.hpp>
#include "../../commonFunctions/CommonFunctions.h"
#include "../enemies/Enemy.h"
#include "../../mainMenu/MainMenu.h"

class MainMenu;

class Level;

class Enemy;

class Hero
{
private:
    sf::Sprite heroSprite;
    sf::Sprite redHealthBarSprite;
    sf::Sprite greenHealthBarSprite;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> walkTextures;
    sf::Clock animationClock;
    int currentFrame = 0;
    bool isAnimating = false;
    sf::Time frameDuration = sf::milliseconds(1000 / 6.);
    sf::Time animationDuration = sf::milliseconds(1000);
    sf::Vector2f heroStandPosition;
    int speedX;
    int speedY;
    int damage[2];
    int health;
    int magicArmor;
    int physicalArmor;
    int attackSpeed;
    bool isHeroFighting = false;
    bool isHeroAlive = true;
public:
    Hero(MainMenu &mainMenu, Level &level, int code);
    void setHealth(int newHealth);
    void setDamage(int newDamage1, int newDamage2);
    void setSpeedX(int newSpeedX);
    void setSpeedY(int newSpeedY);
    void setMagicArmor(int newMagicArmor);
    void setPhysicalArmor(int newPhysicalArmor);
    void setAttackSpeed(int newAttackSpeed);
    void setSprite(sf::Sprite newSprite);

    int getHealth();
    int getDamage();
    int getSpeedX();
    int getSpeedY();
    int getMagicArmor();
    int getPhysicalArmor();
    int getAttackSpeed();
    sf::Sprite &getSprite();

    void setValues(std::vector<std::vector<int>> allStats, int code);

    bool heroMoving(sf::Sprite &sprite, sf::Vector2i &mousePos);

    void setIsHeroFighting(bool newIsHeroMoving);
    bool getIsHeroFighting();

    bool isEnemyInHeroesRange(Enemy *enemy);
    void fighting(Enemy *enemy);

    void setIsHeroAlive(bool condition);
    bool getIsHeroAlive();

    void performAttackAnimation();
    void loadHeroTextures(MainMenu &mainMenu, int code, std::vector<sf::Texture> &textures);

    void performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration);
    std::vector<sf::Texture>& getAttackTexture();
    std::vector<sf::Texture>& getWalkTexture();
};