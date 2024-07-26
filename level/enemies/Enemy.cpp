#include "Enemy.h"

void Enemy::setHealth(int hlth){health = hlth;}
void Enemy::setDamage(int dmg){damage = dmg;}
void Enemy::setSpeedX(int spdX){speedX = spdX;}
void Enemy::setSpeedY(int spdY){speedY = spdY;}
void Enemy::setMagicArmor(int mgcArmr){magicArmor = mgcArmr;}
void Enemy::setPhysicalArmor(int physclArmr){physicalArmor = physclArmr;}
void Enemy::setBounty(int bnty){bounty = bnty;}
void Enemy::setAttckSpd(int attSpd){attackSpeed = attSpd;}


int Enemy::getHealth(){return health;}
int Enemy::getDamage(){return damage;}
int Enemy::getSpeedX(){return speedX;}
int Enemy::getSpeedY(){return speedY;}
int Enemy::getMagicArmor(){return magicArmor;}
int Enemy::getPhysicalArmor(){return physicalArmor;}
int Enemy::getBounty(){return bounty;}
int Enemy::getAttckSpd(){return attackSpeed;}