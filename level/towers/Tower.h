#pragma once

#include <SFML/Graphics.hpp>
#include "../enemies/Enemy.h"

class Tower
{
    // sprite, damage, attackSpeed
    // getters, shootAnimation
private:
    sf::Sprite sprite;
    int cost;
    int damage;
    int shootSpeed;
    int range;

public:
    Tower(/*accepts all needed values from storage in Level class */);
    sf::Sprite getSprite();
    int getCost();
    int getDamage();
    int getShootSpeed();
    int getRange();

    bool isEnemyInRange(Enemy *enemy);
    void shoot(Enemy *enemy);
};