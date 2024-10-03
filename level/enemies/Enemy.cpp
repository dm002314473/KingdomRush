#include "Enemy.h"

int generateRandomNumber(int min, int max);
void stopMoving(sf::Sprite &sprite);
// void moveUp(sf::Sprite &sprite);
// void moveDown(sf::Sprite &sprite);
// void moveLeft(sf::Sprite &sprite);
// void moveRight(sf::Sprite &sprite);

Enemy::Enemy(MainMenu &mainMenu, std::vector<std::vector<int>> &waypoints, std::pair<int, int> pair) : waypoints(waypoints)
{
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), pair.first, 0);
    spriteSetting(sprite, *texture, .2);
    sf::Texture *redBarTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), REDHEALTHBAR, 0);
    spriteSetting(redHealthBarSprite, *redBarTexture, .2);
    sf::Texture *greenBarTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), GREENHEALTHBAR, 0);
    spriteSetting(greenHealthBarSprite, *greenBarTexture, .2);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    redHealthBarSprite.setOrigin(50, 10);
    int positionX = generateRandomNumber(waypoints[0][0] - 150, waypoints[0][0] + 10) - pair.second;
    int positionY = generateRandomNumber(waypoints[0][1] - 150, waypoints[0][1] + 10);
    sprite.setPosition(positionX, positionY);
    redHealthBarSprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10);
    greenHealthBarSprite.setPosition(redHealthBarSprite.getPosition());
    currentWaypointIndex = 0;
    setValues(mainMenu.getEnemyStatsMatrix(), pair.first);
    loadEnemyTextures(mainMenu, pair.first, attackTextures);
    loadEnemyTextures(mainMenu, pair.first + 1, walkingTextures);
    fullHealth = health;
}

void Enemy::setValues(std::vector<std::vector<int>> allStats, int code)
{
    for (int i = 0; i < allStats.size(); i++)
    {
        for (int j = 0; j < allStats[i].size(); j++)
        {
            if (allStats[i][0] == code)
            {
                setDamage(allStats[i][1], allStats[i][2]);
                setHealth(allStats[i][3]);
                setMagicArmor(allStats[i][4]);
                setPhysicalArmor(allStats[i][5]);
                setSpeedX(allStats[i][6]);
                setSpeedY(allStats[i][7]);
                setLiveTaking(allStats[i][8]);
                setBounty(allStats[i][9]);
                setAttackSpeed(allStats[i][10]);
            }
        }
    }
}

void Enemy::setHealth(int newHealth) { health = newHealth; }
void Enemy::setDamage(int newDamage1, int newDamage2)
{
    damage[0] = newDamage1;
    damage[1] = newDamage2;
}
void Enemy::setSpeedX(int newSpeedX) { speedX = newSpeedX; }
void Enemy::setSpeedY(int newSpeedY) { speedY = newSpeedY; }
void Enemy::setMagicArmor(int newMagicArmor) { magicArmor = newMagicArmor; }
void Enemy::setPhysicalArmor(int newPhysicalArmor) { physicalArmor = newPhysicalArmor; }
void Enemy::setBounty(int newBounty) { bounty = newBounty; }
void Enemy::setAttackSpeed(int newAttackSpeed) { attackSpeed = newAttackSpeed; }
void Enemy::setSprite(sf::Sprite newSprite) { sprite = newSprite; }

void Enemy::move(float dtm)
{
    if (shouldEnemyTurn())
        currentWaypointIndex++;

    if (currentWaypointIndex >= waypoints.size()) {
        outOfMap = true;
        return;
    }

    switch (waypoints[currentWaypointIndex][2])
    {
    case 1:
        moveUp(dtm);
        break;
    case 2:
        moveRight(dtm);
        break;
    case 3:
        moveDown(dtm);
        break;
    case 4:
        moveLeft(dtm);
        break;
    default:
        stopMoving(sprite);
        outOfMap = true;
        break;
    }
}

void Enemy::stop()
{
    sprite.setPosition(sprite.getPosition());
}

void stopMoving(sf::Sprite &sprite) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y); }
void Enemy::moveRight(float dtm) { sprite.setPosition(sprite.getPosition().x + speedX * dtm, sprite.getPosition().y); }
void Enemy::moveLeft(float dtm) { sprite.setPosition(sprite.getPosition().x - speedX * dtm, sprite.getPosition().y); }
void Enemy::moveUp(float dtm) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - speedY * dtm); }
void Enemy::moveDown(float dtm) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + speedY * dtm); }


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
int Enemy::getDamage() { return generateRandomNumber(damage[0], damage[1]); }
int Enemy::getSpeedX() { return speedX; }
int Enemy::getSpeedY() { return speedY; }
int Enemy::getMagicArmor() { return magicArmor; }
int Enemy::getPhysicalArmor() { return physicalArmor; }
int Enemy::getBounty() { return bounty; }
int Enemy::getAttackSpeed() { return attackSpeed; }

sf::Sprite Enemy::getSprite() { return sprite; }

void Enemy::setIsEnemyFighting(bool condition) { isEnemyFighting = condition; }
bool Enemy::getIsEnemyFighting() { return isEnemyFighting; }

int generateRandomNumber(int min, int max) { return rand() % (max - min) + min; }

void Enemy::setIsEnemyAlive(bool condition) { isEnemyAlive = condition; }
bool Enemy::getIsEnemyAlive()
{
    if (health > 0)
        return true;
    else
        return false;
}

void Enemy::setLiveTaking(int newLiveTaking) { liveTaking = newLiveTaking; }
int Enemy::getLiveTaking() { return liveTaking; }

void Enemy::fighting(Hero *hero)
{
    hero->setHealth(hero->getHealth() - getDamage());
}

void Enemy::loadEnemyTextures(MainMenu &mainMenu, int code, std::vector<sf::Texture> &textures)
{
    bool rowFound = false;
    for (auto &row : mainMenu.getAllTexturesMatrix())
    {
        if (row.id == code)
        {
            rowFound = true;
            for (size_t i = 0; i < row.textures.size(); ++i)
            {
                sf::Texture texture;
                if (texture.loadFromFile(row.texturePaths[i]))
                    textures.push_back(texture);
                else
                    std::cerr << "Failed to load texture from path: " << row.texturePaths[i] << std::endl;
            }
            break;
        }
    }

    if (!rowFound)
    {
        std::cerr << "No textures found for the code: " << code << std::endl;
    }
}

void Enemy::performAttackAnimation()
{
    if (!isAnimating)
    {
        isAnimating = true;
        currentFrame = 0;
        animationClock.restart();
    }
    if (isAnimating)
    {
        sf::Time elapsedTime = animationClock.getElapsedTime();
        if (elapsedTime >= frameDuration)
        {
            currentFrame++;
            if (currentFrame >= attackTextures.size() || elapsedTime >= animationDuration)
            {
                isAnimating = false;
                currentFrame = 0;
                sprite.setTexture(attackTextures[0]);
                return;
            }
            sprite.setTexture(attackTextures[currentFrame]);
            animationClock.restart();
        }
    }
}

void Enemy::performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration)
{
    if (!isAnimating)
    {
        isAnimating = true;
        currentFrame = 0;
        animationClock.restart();
    }

    if (isAnimating)
    {
        sf::Time elapsedTime = animationClock.getElapsedTime();
        if (elapsedTime >= frameDuration)
        {
            currentFrame++;
            if (currentFrame >= textures.size() || elapsedTime >= animationDuration)
            {
                isAnimating = false;
                currentFrame = 0;
                sprite.setTexture(textures[0]);
                return;
            }
            sprite.setTexture(textures[currentFrame]);
            animationClock.restart();
        }
    }
}

std::vector<sf::Texture>& Enemy::getAttackTexture() { return attackTextures; }
std::vector<sf::Texture>& Enemy::getWalkTexture() { return walkingTextures; }

void Enemy::draw(sf::RenderWindow &window) {
    updateHealthBarsPosition();
    window.draw(sprite);
    window.draw(redHealthBarSprite);
    window.draw(greenHealthBarSprite);
}

void Enemy::updateHealthBarsPosition() {
    redHealthBarSprite.setPosition(sprite.getPosition().x - 40, sprite.getPosition().y  - 70);
    greenHealthBarSprite.setPosition(redHealthBarSprite.getPosition().x -10, redHealthBarSprite.getPosition().y - 2);
}

void Enemy::updateHealthBar(int currentHealth){
    greenHealthBarSprite.setScale(.2 - .2 * (1 - currentHealth * 1. / fullHealth), .2);
}
