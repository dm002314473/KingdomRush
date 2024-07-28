#include "Enemy.h"

Enemy::Enemy(MainMenu &mainMenu)
{
    texture.loadFromFile("GeneralRehearsal/images/giant_walking1.png");
    sprite.setTexture(texture);
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

void Enemy::move(float deltaTime) { 
    sprite.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y - 1); 
    if (currentWaypointIndex < waypoints.size()) {
            sf::Vector2f currentPosition = sprite.getPosition();
            sf::Vector2f targetPosition(waypoints[currentWaypointIndex][0], waypoints[currentWaypointIndex][1]);
            sf::Vector2f direction = targetPosition - currentPosition;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            float speed = 100.0f; // Adjust speed as needed

            if (distance < speed * deltaTime) {
                // Move directly to the waypoint if close enough
                sprite.setPosition(targetPosition);
                currentWaypointIndex++;
            } else {
                // Normalize the direction and move towards the waypoint
                direction /= distance;
                sprite.move(direction * speed * deltaTime);
            }
        }
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

void Enemy::setWaypoints(const std::vector<std::vector<int>>& waypoints){
    this->waypoints = waypoints;
}


int Enemy::generateRandomNumber(int min, int max) {
    if (min > max) {
        std::swap(min, max);
    }
    return min + rand() % (max - min + 1);
}