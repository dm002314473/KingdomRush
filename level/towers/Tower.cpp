#include "Tower.h"

int generateRandomNumber(int min, int max);

Tower::Tower(MainMenu &mainMenu, int code)
{
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), code, 0);
    spriteSetting(sprite, *texture, .3);
    setValues(mainMenu.getTowerStatsMatrix(), code);
    setCode(code);
    setApsoluteCost(getCost());
}

sf::Sprite& Tower::getSprite() { return sprite; }
int Tower::getCost() { return cost; }
int Tower::getDamage() { return generateRandomNumber(damage[0], damage[1]); }
int Tower::getShootSpeed() { return shootSpeed; }
int Tower::getRange() { return range; }
int Tower::getCode() { return code; }
int Tower::getNextLevelCost() { return nextLevelCost; }
int Tower::getApsoluteCost() { return apsoluteCost; }

void Tower::setSprite(sf::Sprite newSprite) { sprite = newSprite; }
void Tower::setCost(int newCost) { cost = newCost; }
void Tower::setDamage(int newDamageMin, int newDamageMax) { 
    damage[0] = newDamageMin;
    damage[1] = newDamageMax;
}
void Tower::setShootSpeed(int newShootSpeed) { shootSpeed = newShootSpeed; }
void Tower::setRange(int newRange) { range = newRange; }
void Tower::setCode(int newCode) { code = newCode; }
void Tower::setNextLevelCost(int newNestLevelCost) { nextLevelCost = newNestLevelCost; }
void Tower::setApsoluteCost(int newApsoluteCost) { apsoluteCost = newApsoluteCost; }

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
                setNextLevelCost(allStats[i][6]);
            }
        }
    }
}

void Tower::handleClick(MainMenu &mainMenu, sf::Vector2i &mousePos){
    if (isClicked(mousePos))
    {
        //openUpgradeMenu(mainMenu);
    }
}

bool Tower::isClicked(sf::Vector2i &mousePos){
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return bounds.contains(mousePos.x, mousePos.y);
}

// sf::Sprite Tower::openUpgradeMenu(MainMenu &mainMenu){
//     std::cout << "ide upgrade" << std::endl;
//     sf::Texture *towerUpgradeMenuTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), WIZ_TOWER_UPGRADE, 0);
//     spriteSetting(towerUpgradeMenu, *towerUpgradeMenuTexture, 1.);
//     towerUpgradeMenu.setOrigin(130, 130);
//     towerUpgradeMenu.setPosition(sprite.getPosition());
//     return towerUpgradeMenu;
// }