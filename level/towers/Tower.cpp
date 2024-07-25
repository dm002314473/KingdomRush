#include "Tower.h"

Tower::Tower(texture, cost, damage, shootSpeed, range) : cost(cost), damage(damage), shootSpeed(shootSpeed), range(range)
{
    sprite.setTexture(texture);
}

sf::Sprite Tower::getSprite() { return sprite; }
int Tower::getCost() { return cost; }
int Tower::getDamage() { return damage; }
int Tower::getShootSpeed() { return shootSpeed; }
int Tower::getRange() { return range; }

bool Tower::isEnemyInRange(Enemy *enemy) {}
void Tower::shoot(Enemy *enemy) {}
