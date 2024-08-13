#include "Enemy.h"



int generateRandomNumber(int min, int max);
void stopMoving(sf::Sprite &sprite);
void moveUp(sf::Sprite &sprite);
void moveDown(sf::Sprite &sprite);
void moveLeft(sf::Sprite &sprite);
void moveRight(sf::Sprite &sprite);

Enemy::Enemy(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints) : waypoints(waypoints)
{

    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), GIANT, 0);
    spriteSetting(sprite, *texture, .2);
    sprite.setOrigin(50, 50);
    int positionX = generateRandomNumber(waypoints[0][0] - 150, waypoints[0][0] + 10);
    int positionY = generateRandomNumber(waypoints[0][1] - 150, waypoints[0][1] + 10);
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
        moveUp(sprite);
        break;
    case 2:
        moveRight(sprite);
        break;
    case 3:
        moveDown(sprite);
        break;
    case 4:
        moveLeft(sprite);
        break;
    default:
        stopMoving(sprite);
        outOfMap = true;
        break;
    }
}

void stopMoving(sf::Sprite &sprite) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y); }
void moveRight(sf::Sprite &sprite) { sprite.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y); }
void moveLeft(sf::Sprite &sprite) { sprite.setPosition(sprite.getPosition().x - 1, sprite.getPosition().y); }
void moveUp(sf::Sprite &sprite) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 1); }
void moveDown(sf::Sprite &sprite) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 1); }

bool Enemy::shouldEnemyTurn()
{
    float dx = sprite.getPosition().x - waypoints[currentWaypointIndex + 1][0];
    float dy = sprite.getPosition().y - waypoints[currentWaypointIndex + 1][1];
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 150)
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

int generateRandomNumber(int min, int max) { return rand() % (max - min) + min; }