#pragma once

#include<vector>
#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::Texture texture;
    sf::Vector2i currentlocation;
    int damage;
    int speedX;
    int speedY;
    int health;
    int magicArmor;
    int physicalArmor;
    int bounty;
    int attackSpeed;
    // sprite, health, damage, speed
    // getters, moveAnimation
public:
    void setHealth(int hlth);
    void setDamage(int dmg);
    void setSpeedX(int spdX);
    void setSpeedY(int spdY);
    void setMagicArmor(int mgcArmr);
    void setPhysicalArmor(int physclArmr);
    void setBounty(int bnty);
    void setAttckSpd(int attSpd);
    
    int getHealth();
    int getDamage();
    int getSpeedX();
    int getSpeedY();
    int getMagicArmor();
    int getPhysicalArmor();
    int getBounty();
    int getAttckSpd();
};