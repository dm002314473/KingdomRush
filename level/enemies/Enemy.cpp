#include "Enemy.h"

void Enemy::setHealth(int newHealth){health = newHealth;}
void Enemy::setDamage(int newDamage){damage = newDamage;}
void Enemy::setSpeedX(int newSpeedX){speedX = newSpeedX;}
void Enemy::setSpeedY(int newSpeedY){speedY = newSpeedY;}
void Enemy::setMagicArmor(int newMagicArmor){magicArmor = newMagicArmor;}
void Enemy::setPhysicalArmor(int newPhysicalArmor){physicalArmor = newPhysicalArmor;}
void Enemy::setBounty(int newBounty){bounty = newBounty;}
void Enemy::setAttackSpeed(int newAttackSpeed){attackSpeed = newAttackSpeed;}
void Enemy::setSprite(sf::Sprite newSprite){sprite = newSprite;}


int Enemy::getHealth(){return health;}
int Enemy::getDamage(){return damage;}
int Enemy::getSpeedX(){return speedX;}
int Enemy::getSpeedY(){return speedY;}
int Enemy::getMagicArmor(){return magicArmor;}
int Enemy::getPhysicalArmor(){return physicalArmor;}
int Enemy::getBounty(){return bounty;}
int Enemy::getAttackSpeed(){return attackSpeed;}

sf::Sprite Enemy::getSprite() { return sprite; }
