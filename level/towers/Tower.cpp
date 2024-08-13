#include "Tower.h"

int generateRandomNumber(int min, int max);

Tower::Tower(MainMenu &mainMenu, int code)
{
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), code, 0);
    spriteSetting(sprite, *texture, .3);
    setValues(mainMenu.getTowerStatsMatrix(), code);
}

sf::Sprite Tower::getSprite() { return sprite; }
int Tower::getCost() { return cost; }
int Tower::getDamage() { return generateRandomNumber(damage[0], damage[1]); }
int Tower::getShootSpeed() { return shootSpeed; }
int Tower::getRange() { return range; }

void Tower::setSprite(sf::Sprite newSprite) { sprite = newSprite; }
void Tower::setCost(int newCost) { cost = newCost; }
void Tower::setDamage(int newDamageMin, int newDamageMax) { 
    damage[0] = newDamageMin;
    damage[1] = newDamageMax;
}
void Tower::setShootSpeed(int newShootSpeed) { shootSpeed = newShootSpeed; }
void Tower::setRange(int newRange) { range = newRange; }

bool Tower::isEnemyInRange(Enemy *enemy) {return true;}
void Tower::shoot(Enemy *enemy) {}

void Tower::setPosition(int x, int y) { sprite.setPosition(x, y); }

sf::Vector2f Tower::getPosition() { return sf::Vector2f(sprite.getPosition()); }

void Tower::setValues(std::vector<std::vector<int>> allStats, int code){
    for (int i = 0; i < allStats.size(); i++){
        for (int j = 0; j < allStats[i].size(); j++){
            if(allStats[i][0] == code){
                setCost(allStats[i][1]);
                setDamage(allStats[i][2], allStats[i][3]);
                setShootSpeed(allStats[i][4]);
                setRange(allStats[i][5]);
            }
        }
    }
}