#include "Hero.h"

int generateRandomNumber(int min, int max);
bool isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius);

Hero::Hero(MainMenu &mainMenu, Level &level, int code)
{
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), HERO1, 0);
    spriteSetting(heroSprite, *texture, .2);
    setValues(mainMenu.getEnemyStatsMatrix(), code);
    heroStandPosition = level.getHeroStandPosition();
    heroSprite.setPosition(heroStandPosition);
    heroSprite.setOrigin(150, 150);
    loadHeroTextures(mainMenu, 90015, attackTextures);
    loadHeroTextures(mainMenu, 90016, walkTextures);
}

void Hero::setValues(std::vector<std::vector<int>> allStats, int code)
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
                setAttackSpeed(allStats[i][10]);
            }
        }
    }
}

void Hero::setHealth(int newHealth) { health = newHealth; }
void Hero::setDamage(int newDamage1, int newDamage2)
{
    damage[0] = newDamage1;
    damage[1] = newDamage2;
}
void Hero::setSpeedX(int newSpeedX) { speedX = newSpeedX; }
void Hero::setSpeedY(int newSpeedY) { speedY = newSpeedY; }
void Hero::setMagicArmor(int newMagicArmor) { magicArmor = newMagicArmor; }
void Hero::setPhysicalArmor(int newPhysicalArmor) { physicalArmor = newPhysicalArmor; }
void Hero::setAttackSpeed(int newAttackSpeed) { attackSpeed = newAttackSpeed; }
void Hero::setSprite(sf::Sprite newSprite) { heroSprite = newSprite; }

int Hero::getHealth() { return health; }
int Hero::getDamage() { return generateRandomNumber(damage[0], damage[1]); }
int Hero::getSpeedX() { return speedX; }
int Hero::getSpeedY() { return speedY; }
int Hero::getMagicArmor() { return magicArmor; }
int Hero::getPhysicalArmor() { return physicalArmor; }
int Hero::getAttackSpeed() { return attackSpeed; }
sf::Sprite &Hero::getSprite() { return heroSprite; }

bool Hero::heroMoving(sf::Sprite &sprite, sf::Vector2i &mousePos)
{
    int moveX = 0, moveY = 0;
    sf::Vector2f currentPos = sprite.getPosition();
    if (currentPos.x < mousePos.x)
        moveX = 1;
    else if (currentPos.x > mousePos.x)
        moveX = -1;

    if (currentPos.y < mousePos.y)
        moveY = 1;
    else if (currentPos.y > mousePos.y)
        moveY = -1;

    sprite.setPosition(currentPos.x + moveX, currentPos.y + moveY);

    if (static_cast<int>(currentPos.x) == mousePos.x && static_cast<int>(currentPos.y) == mousePos.y)
        return true;
    return false;
}

void Hero::setIsHeroFighting(bool newIsHeroFighting) { isHeroFighting = newIsHeroFighting; }
bool Hero::getIsHeroFighting() { return isHeroFighting; }

bool Hero::isEnemyInHeroesRange(Enemy *enemy)
{
    if (isPointInCircle(enemy->getSprite().getPosition(), heroSprite.getPosition(), 150))
        return true;
    return false;
}

bool isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius)
{
    float distance = std::sqrt(std::pow(point.x - circleCenter.x, 2) + std::pow(point.y - circleCenter.y, 2));
    return distance <= radius;
}

void Hero::setIsHeroAlive(bool condition) { isHeroAlive = condition; }
bool Hero::getIsHeroAlive()
{
    if (health > 0)
        isHeroAlive = true;
    else
        isHeroAlive = false;
    return isHeroAlive;
}

void Hero::fighting(Enemy *enemy) { enemy->setHealth(enemy->getHealth() - getDamage()); }

void Hero::loadHeroTextures(MainMenu &mainMenu, int code, std::vector<sf::Texture> &textures)
{
    bool rowFound = false;
    for (auto &row : mainMenu.getAllTexturesMatrix())
    {
        if (row.id == code)
        {
            rowFound = true;
            for (size_t i = 0; i < row.textures.size() - 1; ++i)
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
        std::cerr << "No textures found for the code: " << code << std::endl;
}

void Hero::performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration)
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
                heroSprite.setTexture(textures[0]);
                return;
            }
            heroSprite.setTexture(textures[currentFrame]);
            animationClock.restart();
        }
    }
}

std::vector<sf::Texture> &Hero::getAttackTexture() { return attackTextures; }
std::vector<sf::Texture> &Hero::getWalkTexture() { return walkTextures; }