#include "Tower.h"
#include "../enemies/Enemy.h"

int generateRandomNumber(int min, int max);

Tower::Tower(MainMenu &mainMenu, int code) : currentTarget(nullptr), hasTarget(false)
{
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), code, 0);
    spriteSetting(sprite, *texture, .3);
    setValues(mainMenu.getTowerStatsMatrix(), code);
    setCode(code);
    setApsoluteCost(getCost());
    attackCooldown = 1000;
}

sf::Sprite &Tower::getSprite() { return sprite; }
int Tower::getCost() { return cost; }
int Tower::getDamage() { return generateRandomNumber(damage[0], damage[1]); }
int Tower::getShootSpeed() { return shootSpeed; }
int Tower::getRange() { return range; }
int Tower::getCode() { return code; }
int Tower::getNextLevelCost() { return nextLevelCost; }
int Tower::getApsoluteCost() { return apsoluteCost; }

void Tower::setSprite(sf::Sprite newSprite) { sprite = newSprite; }
void Tower::setCost(int newCost) { cost = newCost; }
void Tower::setDamage(int newDamageMin, int newDamageMax)
{
    damage[0] = newDamageMin;
    damage[1] = newDamageMax;
}
void Tower::setShootSpeed(int newShootSpeed) { shootSpeed = newShootSpeed; }
void Tower::setRange(int newRange) { range = newRange; }
void Tower::setCode(int newCode) { code = newCode; }
void Tower::setNextLevelCost(int newNestLevelCost) { nextLevelCost = newNestLevelCost; }
void Tower::setApsoluteCost(int newApsoluteCost) { apsoluteCost = newApsoluteCost; }

bool Tower::isEnemyInRange(Enemy *enemy)
{
    // std::cout << calculateDistance(enemy, this) << std::endl;
    // std::cout << (calculateDistance(enemy, this) <= range) << std::endl;
    if (calculateDistance(enemy, this) <= range)
        return true;
    return false;
}

double Tower::calculateDistance(Enemy *enemy, Tower *tower)
{
    double distanceX = enemy->getSprite().getPosition().x - tower->getSprite().getPosition().x;
    double distanceY = enemy->getSprite().getPosition().y - tower->getSprite().getPosition().y;
    double distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    return distance;
}

void Tower::shoot(std::vector<Enemy *> &enemies, sf::Time deltaTime)
{
    timeSinceLastShot += deltaTime;

    if (timeSinceLastShot.asMilliseconds() >= attackCooldown && hasTarget && currentTarget)
    {
        if (currentTarget->getHealth() > 0)
            currentTarget->setHealth(currentTarget->getHealth() - getDamage());
        else
            currentTarget->setIsEnemyAlive(false);
        std::cout << "currentTarget health:" << currentTarget->getHealth() << std::endl;
        std::cout << "currentTower damage:" << getDamage() << std::endl;

        timeSinceLastShot = sf::Time::Zero;
    }
}

bool Tower::getHasTarget() { return hasTarget; }
void Tower::setHasTarget(bool set) { hasTarget = set; }
Enemy *Tower::getCurrentEnemy() { return currentTarget; }
void Tower::setCurrentEnemy(Enemy *enemy) { currentTarget = enemy; }

void Tower::setPosition(int x, int y) { sprite.setPosition(x, y); }

sf::Vector2f Tower::getPosition() { return sf::Vector2f(sprite.getPosition()); }

void Tower::setValues(std::vector<std::vector<int>> allStats, int code)
{
    for (int i = 0; i < allStats.size(); i++)
    {
        for (int j = 0; j < allStats[i].size(); j++)
        {
            if (allStats[i][0] == code)
            {
                setCost(allStats[i][1]);
                setDamage(allStats[i][2], allStats[i][3]);
                setShootSpeed(allStats[i][4]);
                setRange(allStats[i][5]);
                setNextLevelCost(allStats[i][6]);
            }
        }
    }
}

bool Tower::isClicked(sf::Vector2i &mousePos)
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return bounds.contains(mousePos.x, mousePos.y);
}

sf::CircleShape &Tower::getShootRadius() { return shootRadius; }
void Tower::setShootingRadius(float radius, sf::Vector2f radiusPosition, float transparency)
{
    shootRadius.setRadius(radius);
    shootRadius.setOrigin(radius, radius);
    shootRadius.setFillColor(sf::Color(255, 255, 255, transparency));
    shootRadius.setPosition(radiusPosition);
}