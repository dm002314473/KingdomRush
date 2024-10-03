#include "Soldier.h"

int generateRandomNumber(int min, int max);
bool isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius);

Soldier::Soldier(MainMenu &mainMenu, Level &level, int code, Tower &tower)
{
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), code, 0);
    spriteSetting(soldierSprite, *texture, .2);
    setValues(mainMenu.getEnemyStatsMatrix(), code);
    soldierStandPosition = tower.getPosition();
    soldierSprite.setPosition(soldierStandPosition);
    soldierSprite.setOrigin(150, 150);
    loadSoldierTextures(mainMenu, 90015, attackTextures);
    loadSoldierTextures(mainMenu, 90016, walkTextures);
    sf::Texture *redBarTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), REDHEALTHBAR, 0);
    spriteSetting(redHealthBarSprite, *redBarTexture, .2);
    sf::Texture *greenBarTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), GREENHEALTHBAR, 0);
    spriteSetting(greenHealthBarSprite, *greenBarTexture, .2);
    redHealthBarSprite.setOrigin(50, 10);
    redHealthBarSprite.setPosition(soldierSprite.getPosition().x, soldierSprite.getPosition().y - 10);
    greenHealthBarSprite.setPosition(redHealthBarSprite.getPosition());
    fullHealth = health;
    shouldSoldierHeal = false;
}

void Soldier::setValues(std::vector<std::vector<int>> allStats, int code)
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
                setHealPerSecond(allStats[i][9]);
                setAttackSpeed(allStats[i][10]);
            }
        }
    }
}

void Soldier::setHealth(int newHealth) { health = newHealth; }
void Soldier::setDamage(int newDamage1, int newDamage2)
{
    damage[0] = newDamage1;
    damage[1] = newDamage2;
}
void Soldier::setSpeedX(int newSpeedX) { speedX = newSpeedX; }
void Soldier::setSpeedY(int newSpeedY) { speedY = newSpeedY; }
void Soldier::setMagicArmor(int newMagicArmor) { magicArmor = newMagicArmor; }
void Soldier::setPhysicalArmor(int newPhysicalArmor) { physicalArmor = newPhysicalArmor; }
void Soldier::setAttackSpeed(int newAttackSpeed) { attackSpeed = newAttackSpeed; }
void Soldier::setSprite(sf::Sprite newSprite) { soldierSprite = newSprite; }

int Soldier::getHealth() { return health; }
int Soldier::getDamage() { return generateRandomNumber(damage[0], damage[1]); }
int Soldier::getSpeedX() { return speedX; }
int Soldier::getSpeedY() { return speedY; }
int Soldier::getMagicArmor() { return magicArmor; }
int Soldier::getPhysicalArmor() { return physicalArmor; }
int Soldier::getAttackSpeed() { return attackSpeed; }
sf::Sprite &Soldier::getSprite() { return soldierSprite; }

bool Soldier::soldierMoving(sf::Sprite &sprite, sf::Vector2i &mousePos)
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

    if (int(currentPos.x) == mousePos.x && int(currentPos.y) == mousePos.y)
        return true;
    return false;
}

void Soldier::setIsSoldierFighting(bool newIssoldierFighting) { isSoldierFighting = newIssoldierFighting; }
bool Soldier::getIsSoldierFighting() { return isSoldierFighting; }

bool Soldier::isEnemyInSoldieresRange(Enemy *enemy)
{
    if (isPointInCircle(enemy->getSprite().getPosition(), soldierSprite.getPosition(), 150))
        return true;
    return false;
}

void Soldier::setIsSoldierAlive(bool condition) { isSoldierAlive = condition; }
bool Soldier::getIsSoldierAlive()
{
    if (health > 0)
        isSoldierAlive = true;
    else
        isSoldierAlive = false;
    return isSoldierAlive;
}

void Soldier::fighting(Enemy *enemy) { enemy->setHealth(enemy->getHealth() - getDamage()); }

void Soldier::loadSoldierTextures(MainMenu &mainMenu, int code, std::vector<sf::Texture> &textures)
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

void Soldier::performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration)
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
                soldierSprite.setTexture(textures[0]);
                return;
            }
            soldierSprite.setTexture(textures[currentFrame]);
            animationClock.restart();
        }
    }
}

std::vector<sf::Texture>& Soldier::getAttackTexture() { return attackTextures; }
std::vector<sf::Texture>& Soldier::getWalkTexture() { return walkTextures; }

void Soldier::draw(sf::RenderWindow &window) {
    updateHealthBarsPosition();
    window.draw(soldierSprite);
    window.draw(redHealthBarSprite);
    window.draw(greenHealthBarSprite);
}

void Soldier::updateHealthBarsPosition() {
    redHealthBarSprite.setPosition(soldierSprite.getPosition().x - 40, soldierSprite.getPosition().y  - 70);
    greenHealthBarSprite.setPosition(redHealthBarSprite.getPosition().x -10, redHealthBarSprite.getPosition().y - 2);
}

void Soldier::updateHealthBar(int currentHealth){
    greenHealthBarSprite.setScale(.2 - .2 * (1 - currentHealth * 1. / fullHealth), .2);
}

bool Soldier::isSoldierPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor){
    for (int i = 0; i < colors.size(); i++)
        if(colors[i] == pixelColor)
            return true;
    return false;
}

int Soldier::getFullHealth() { return fullHealth; }

bool Soldier::getShouldSoldierHeal() { return shouldSoldierHeal; }
void Soldier::setShouldSoldierHeal(bool condition) { shouldSoldierHeal = condition; }

int Soldier::getHealPerSecond() { return healPerSecond; }
void Soldier::setHealPerSecond(int newHealPerSecond) { healPerSecond = newHealPerSecond; }
