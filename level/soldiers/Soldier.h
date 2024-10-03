#pragma once

#include <SFML/Graphics.hpp>
#include "../../commonFunctions/CommonFunctions.h"
#include "../enemies/Enemy.h"
#include "../../mainMenu/MainMenu.h"

class MainMenu;

class Level;

class Enemy;

class Tower;

class Soldier
{
private:
    sf::Sprite soldierSprite;
    sf::Sprite redHealthBarSprite;
    sf::Sprite greenHealthBarSprite;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> walkTextures;
    sf::Clock animationClock;
    int currentFrame = 0;
    bool isAnimating = false;
    sf::Time frameDuration = sf::milliseconds(1000 / 6.);
    sf::Time animationDuration = sf::milliseconds(1000);
    sf::Vector2f soldierStandPosition;
    int speedX;
    int speedY;
    int damage[2];
    int health;
    int magicArmor;
    int physicalArmor;
    int attackSpeed;
    bool isSoldierFighting = false;
    bool isSoldierAlive = true;
    int fullHealth;
    bool shouldSoldierHeal;
    int healPerSecond;

public:
    Soldier(MainMenu &mainMenu, Level &level, int code, Tower &tower);
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

    bool soldierMoving(sf::Sprite &sprite, sf::Vector2i &mousePos);

    void setIsSoldierFighting(bool newIsSoldierMoving);
    bool getIsSoldierFighting();

    bool isEnemyInSoldieresRange(Enemy *enemy);
    void fighting(Enemy *enemy);

    void setIsSoldierAlive(bool condition);
    bool getIsSoldierAlive();

    void performAttackAnimation();
    void loadSoldierTextures(MainMenu &mainMenu, int code, std::vector<sf::Texture> &textures);

    void performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration);
    std::vector<sf::Texture>& getAttackTexture();
    std::vector<sf::Texture>& getWalkTexture();
    
    void draw(sf::RenderWindow &window);
    void updateHealthBarsPosition();
    void updateHealthBar(int currentHealth);

    bool isSoldierPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor);
    int getFullHealth();

    bool getShouldSoldierHeal();
    void setShouldSoldierHeal(bool condition);

    int getHealPerSecond();
    void setHealPerSecond(int newHealPerSecond);
};