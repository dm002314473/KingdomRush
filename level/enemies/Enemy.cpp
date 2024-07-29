#include "Enemy.h"

Enemy::Enemy(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints) : waypoints(waypoints)
{

    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 50000, 0);
    sprite.setTexture(*texture);
    sprite.setOrigin(250, 250);
    sprite.setScale(.2, .2);
    int positionX = generateRandomNumber(waypoints[0][0] - 70, waypoints[0][0] + 70);
    int positionY = generateRandomNumber(waypoints[0][1] - 70, waypoints[0][1] + 70);
    sprite.setPosition(positionX, positionY);

    currentWaypointIndex = 0;
}

void Enemy::setHealth(int newHealth) { health = newHealth; }
void Enemy::setDamage(int newDamage) { damage = newDamage; }
void Enemy::setSpeedX(int newSpeedX) { speedX = newSpeedX; }
void Enemy::setSpeedY(int newSpeedY) { speedY = newSpeedY; }
void Enemy::setMagicArmor(int newMagicArmor) { magicArmor = newMagicArmor; }
void Enemy::setPhysicalArmor(int newPhysicalArmor) { physicalArmor = newPhysicalArmor; }
void Enemy::setBounty(int newBounty) { bounty = newBounty; }
void Enemy::setAttackSpeed(int newAttackSpeed) { attackSpeed = newAttackSpeed; }
void Enemy::setSprite(sf::Sprite newSprite) { sprite = newSprite; }

void Enemy::move()
{
    if (shouldEnemyTurn())
        currentWaypointIndex++;

    switch (waypoints[currentWaypointIndex][2])
    {
    case 1:
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 1);
        break;
    case 2:
        sprite.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y);
        break;
    case 3:
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 1);
        break;
    case 4:
        sprite.setPosition(sprite.getPosition().x - 1, sprite.getPosition().y);
        break;
    default:
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        outOfMap = true;
        break;
    }
}

bool Enemy::shouldEnemyTurn()
{
    float dx = sprite.getPosition().x - waypoints[currentWaypointIndex + 1][0];
    float dy = sprite.getPosition().y - waypoints[currentWaypointIndex + 1][1];
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 100)
        return true;
    return false;
}

int Enemy::getHealth() { return health; }
int Enemy::getDamage() { return damage; }
int Enemy::getSpeedX() { return speedX; }
int Enemy::getSpeedY() { return speedY; }
int Enemy::getMagicArmor() { return magicArmor; }
int Enemy::getPhysicalArmor() { return physicalArmor; }
int Enemy::getBounty() { return bounty; }
int Enemy::getAttackSpeed() { return attackSpeed; }

sf::Sprite Enemy::getSprite() { return sprite; }

int Enemy::generateRandomNumber(int min, int max) { return rand() % (max - min) + min; }