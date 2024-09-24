#include "Level.h"

bool isSpriteClicked(sf::Vector2i &mousePos, sf::Sprite &menuStand);
int whichTowerToCreate(sf::Vector2i &mousePos, sf::Sprite &menuStand);
bool isThereTowerAlready(std::vector<Tower *> &towers, sf::Sprite stand);
void pauseLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused);
void continueLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused);
sf::Vector2f getCenter(sf::Sprite sprite);

Level::Level(int levelIndex, MainMenu &MainMenu) : mainMenu(MainMenu), isLevelPaused(false)
{
    std::string levelFile = "GeneralRehearsal\\level\\lvl" + std::to_string(levelIndex) + ".txt";
    readingLevelData(levelFile);
    sf::Texture *backgroundTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), levelIndex, 0);
    levelBackground.setTexture(*backgroundTexture);
    levelBackgroundTexture = backgroundTexture;

    int polje[5][2] = {{20, 20}, {1800, 20}, {-1000, -1000}, {-500, -500}, {-500, 500}};
    int sifre[5] = {WAVE_SIGN, PAUSE, FORPAUSE, EXIT, CONTINUE};
    for (int i = 0; i < 5; i++)
    {
        sf::Texture *buttonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), sifre[i], 0);
        sf::Sprite *button = new sf::Sprite();
        spriteSetting(*button, *buttonTexture, 0.2);
        button->setPosition(polje[i][0], polje[i][1]);
        buttons.push_back(button);
    }

    settingTowerStands();

    sf::Texture *menuStandTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), TOWER_MENU, 0);
    spriteSetting(menuStand, *menuStandTexture, 1.);
    menuStand.setOrigin(130, 130);
    menuStand.setPosition(-1000, -1000);

    sf::Texture *towerUpgradeMenuTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), TOWER_UPGRADE, 0);
    spriteSetting(towerUpgrade, *towerUpgradeMenuTexture, 1.);
    towerUpgrade.setPosition(-1000, -1000);
    isTowerUpgradeOpen = false;

    sf::Texture *towerUpgradeSplitMenuTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), TOWER_UPGRADE_SPLIT, 0);
    spriteSetting(towerUpgradeSplit, *towerUpgradeSplitMenuTexture, 1.);
    towerUpgradeSplit.setPosition(-1000, -1000);
    isTowerUpgradeSplitOpen = false;

    sf::Texture *towerAbilityUpgradeMenuTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), ABILITY_UPGRADE_MENU, 0);
    spriteSetting(towerAbilityUpgrade, *towerAbilityUpgradeMenuTexture, 1.);
    towerAbilityUpgrade.setPosition(-1000, -1000);
    isAbilityUpgradeOpen = false;

    setMoney(1000);
    if (!font.loadFromFile("GeneralRehearsal/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf")) {
        return ;
    }
    setTextBox(moneyText, font, moneyBox);
    ss << getMoney();
    moneyText.setString(ss.str());

    createHero(HERO1);
}

void Level::setMoney(int newMoney) { money = newMoney; }
int Level::getMoney() { return money; }

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Vector2i &mousePos, Game &game, bool &exitLevel)
{
    // Handle creating towers, and starting new waves
    if (buttons[1]->getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        if (isLevelPaused == true) 
            pauseLevel(buttons, isLevelPaused);
        else
            continueLevel(buttons, isLevelPaused);
        buttons[1]->setPosition(-500, -500);
    }

    if (isButtonClicked(*buttons[3], mousePos))
        exitLevel = true;
    if (isButtonClicked(*buttons[4], mousePos))
    {
        buttons[1]->setPosition(1800, 20);
        buttons[4]->setPosition(-500, -500);
        buttons[3]->setPosition(-500, -500);
        buttons[2]->setPosition(-1000, -1000);
        isLevelPaused = false;
    }
    if (!isLevelPaused) {
        sf::Image image = levelBackgroundTexture->copyToImage();
        sf::Color pixelColor = image.getPixel(mousePos.x, mousePos.y);
        sf::Color colorToCheck(105, 176, 37);
        if (isSpriteClicked(mousePos, hero->getSprite()))
            isHeroSelected = true;
        else if (isHeroSelected && pixelColor != colorToCheck) {
            targetPos = mousePos;
            isHeroSelected = false;
            isHeroMoving = true;
        }

        if (buttons[0]->getGlobalBounds().contains((sf::Vector2f)mousePos)) {
            buttons[0]->setPosition(-1000, -1000);
            startNewWave(wave);
            wave++;
        }

        if (isMenuStandOpen && !isSpriteClicked(mousePos, menuStand)) {
            isMenuStandOpen = false;
            menuStand.setPosition(-1000, -1000);
        }

        if (!isMenuStandOpen) {
            for (auto stand : towerStands) {
                if (stand->getGlobalBounds().contains((sf::Vector2f)mousePos) && !isThereTowerAlready(towers, *stand)) {
                    menuStand.setPosition(stand->getPosition().x - 178, stand->getPosition().y - 202);
                    isMenuStandOpen = true;
                    break;
                }
            }
        } 
        else if (isMenuStandOpen && isSpriteClicked(mousePos, menuStand)) {
            handleMenuClickEvent(mousePos, menuStand);
        }

        for (auto tower : towers) {
            if (tower->isClicked(mousePos)) {
                selectedTower = tower;
                if (tower->getCode() % 10000 == 0 || tower->getCode() % 10000 == 1) {
                    openTowerUpgradeMenu(tower);
                    break;
                }
                else if (tower->getCode() % 10000 == 2) {
                    openTowerUpgradeSplitMenu(tower);
                    break;
                }
                else {
                    openAbilityUpgradeMenu(tower);
                    break;
                }
            }
        }

        if (isTowerUpgradeOpen) {
            if (!isSpriteClicked(mousePos, towerUpgrade))
                closeAllUpgradeMenus();
            else
                if (selectedTower != nullptr){
                    isRadiusVisible = true;
                    handleUpgradeTowerClickEvent(mousePos, towerUpgrade, selectedTower);
                }
        }

        if (isTowerUpgradeSplitOpen) {
            if (!isSpriteClicked(mousePos, towerUpgradeSplit))
                closeAllUpgradeMenus();
            else
                if (selectedTower != nullptr){
                    isRadiusVisible = true;
                    handleUpgradeSplitTowerClickEvent(mousePos, towerUpgradeSplit, selectedTower);
                }
        }

        if (isAbilityUpgradeOpen) {
            if (!isSpriteClicked(mousePos, towerAbilityUpgrade))
                closeAllUpgradeMenus();
            else
                if (selectedTower != nullptr){
                    isRadiusVisible = true;
                    handleAbilityUpgradeTowerClickEvent(mousePos, towerAbilityUpgrade, selectedTower);
                }
        }

    }
}


bool isThereTowerAlready(std::vector<Tower *> &towers, sf::Sprite stand)
{
    for(auto tower : towers)
        if(tower->getPosition().x + 253 == stand.getPosition().x && tower->getPosition().y + 352 == stand.getPosition().y)
            return true;

    return false;
}

void pauseLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused)
{
    buttons[4]->setPosition(-500, -500);
    buttons[3]->setPosition(-500, -500);
    buttons[2]->setPosition(-1000, -1000);
    isLevelPaused = false;
}

void continueLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused)
{
    buttons[2]->setPosition(960, 540);
    buttons[3]->setPosition(1060, 540);
    buttons[4]->setPosition(860, 540);
    isLevelPaused = true;
}

void Level::handleMenuClickEvent(sf::Vector2i &mousePos, sf::Sprite &menuStand)
{
    int towerMark = whichTowerToCreate(mousePos, menuStand);
    switch (towerMark)
    {
    case 1:
        if (getMoney() >= 100)
        {
            createTower(WIZ_LVL1, menuStand);
            menuStand.setPosition(-1000, -1000);
            isMenuStandOpen = false;
            updateMoney(100);
        }
        break;
    case 2:
        if (getMoney() >= 70)
        {
            createTower(ARC_LVL1, menuStand);
            menuStand.setPosition(-1000, -1000);
            isMenuStandOpen = false;
            updateMoney(70);
        }
        break;
    case 3:
        if (getMoney() >= 70)
        {
            createTower(BARRACKS_LVL1, menuStand);
            menuStand.setPosition(-1000, -1000);
            isMenuStandOpen = false;
            updateMoney(70);
        }
        break;
    case 4:
        if (getMoney() >= 120)
        {
            createTower(BOMBARD_LVL1, menuStand);    
            menuStand.setPosition(-1000, -1000);
            isMenuStandOpen = false;
            updateMoney(120);
        }
        break;
    default:
        std::cout << "error" << std::endl;
        break;
    }
}

int whichTowerToCreate(sf::Vector2i &mousePos, sf::Sprite &menuStand)
{
    if (mousePos.y > menuStand.getPosition().y - 130 && mousePos.y < menuStand.getPosition().y - 50)
    {
        if (mousePos.x > menuStand.getPosition().x - 130 && mousePos.x < menuStand.getPosition().x - 50)
            return 1;
        else if (mousePos.x < menuStand.getPosition().x + 130 && mousePos.x > menuStand.getPosition().x + 50)
            return 2;
    }
    else if (mousePos.y < menuStand.getPosition().y + 130 && mousePos.y > menuStand.getPosition().y + 50)
    {
        if (mousePos.x < menuStand.getPosition().x + 130 && mousePos.x > menuStand.getPosition().x + 50)
            return 4;
        else if (mousePos.x > menuStand.getPosition().x - 130 && mousePos.x < menuStand.getPosition().x - 50)
            return 3;
    }
    return -1;
}

bool isSpriteClicked(sf::Vector2i &mousePos, sf::Sprite &sprite)
{
    if (isButtonClicked(sprite, mousePos))
        return true;
    return false;
}

void Level::update()
{
    if (isLevelPaused)
        return;

    int startNewWaveFlag = 1;

    for (auto it = enemies.begin(); it != enemies.end();)
    {
        if(hero->isEnemyInHeroesRange(*it) && !hero->getIsHeroFighting()){
            (*it)->setIsEnemyFighting(true);
            fightingEnemy = *it;
            hero->setIsHeroFighting(true);
        }

        if(!(*it)->getIsEnemyFighting()){
            (*it)->move();
            (*it)->performAnimation((*it)->getWalkTexture(), sf::milliseconds(1000));
        }

        if((*it)->getSprite().getPosition().x < 0)
            startNewWaveFlag = -1;

        if ((*it)->isOutOfMap()) {
            delete *it;
            it = enemies.erase(it);
        }
        else
            ++it;

    }

    if(startNewWaveFlag == 1)
        buttons[0]->setPosition(20, 20);

    if (fightingEnemy != nullptr && !fightingEnemy->getIsEnemyAlive())
        fightingEnemy = nullptr;

    sf::Time timeSinceLastHeroAttack = sf::Time::Zero;
    sf::Time timeSinceLastEnemyAttack = sf::Time::Zero;
    if(fightingEnemy != nullptr)
        enemyAttackInterval = sf::milliseconds(fightingEnemy->getAttackSpeed());
    heroAttackInterval = sf::milliseconds(hero->getAttackSpeed());

    if (isHeroMoving) {
        hero->setIsHeroFighting(false);
        hero->performAnimation(hero->getWalkTexture(), sf::milliseconds(1000));
        if (hero->heroMoving(hero->getSprite(), targetPos)) {
            isHeroMoving = false;
        }
    }
    if(fightingEnemy != nullptr)
        performBattle(hero, fightingEnemy, enemies);

    clock.restart();

    // Implement logic for tower shooting, tower.getdamage should be updated here so its random on every shoot
}

void Level::render(sf::RenderWindow &window)
{
    window.draw(levelBackground);
    for (auto &towerStand : towerStands)
        window.draw(*towerStand);
    for (auto &tower : towers)
        window.draw(tower->getSprite());
    for (auto &enemy : enemies)
        window.draw(enemy->getSprite());
    window.draw(menuStand);
    window.draw(towerUpgrade);
    window.draw(towerUpgradeSplit);
    window.draw(towerAbilityUpgrade);
    window.draw(moneyBox);
    window.draw(moneyText);
    window.draw(hero->getSprite());
    if(isRadiusVisible)
        window.draw(radius);
    for (auto &button : buttons)
        window.draw(*button);
}

void Level::readingLevelData(std::string &levelTxtFile)
{
    std::ifstream file(levelTxtFile);
    if (!file.is_open())
    {
        std::cerr << "Unable to open " << levelTxtFile << std::endl;
        return;
    }
    std::string line;
    std::string currentState;
    Wave newWave;
    int prevLevelIndex = 1;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        iss >> word;
        if (word == "waypoints" || word == "tower" || word == "hero" || word.find("wave") != std::string::npos)
            currentState = word;
        else
        {
            std::istringstream iss(line);
            int x, y, direction;
            char comma;
            iss.seekg(0);
            iss >> x >> comma >> y >> direction;
            if (comma != ',')
            {
                std::cerr << "Error: Expected comma between coordinates." << std::endl;
                continue;
            }
            std::vector<int> position = {x, y, direction};
            std::vector<int> directionVector;
            if (currentState == "waypoints")
                waypoints.push_back(position);
            else if (currentState == "tower")
                towerStandsPositions.push_back(position);
            else if(currentState == "hero")
                heroStandPosition = position;
            else if(currentState.find("wave") != std::string::npos){
                int levelIndex = currentState[4] - '0';
                if (levelIndex != prevLevelIndex) {
                    levelWaves.push_back(newWave);
                    newWave.erase();
                    prevLevelIndex++;
                }
                newWave.pushEnemyToWave(x, y);
            }
        }
    }
    file.close();

    levelWaves.push_back(newWave);
}

void Level::startNewWave(int waveIndex){
    levelWaves[waveIndex];
    for (int i = 0; i < levelWaves[waveIndex].getSize(); i++){
        Enemy *enemy1 = new Enemy(mainMenu, waypoints, levelWaves[waveIndex].getEnemy(i));   
        enemies.push_back(enemy1);
    }
}

void Level::settingTowerStands()
{
    sf::Texture *towerStandTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), TOWER_STAND, 0);
    for (auto stand : towerStands)
        delete stand;
    towerStands.clear();

    for (size_t i = 0; i < towerStandsPositions.size(); i++)
    {
        sf::Sprite *stand = new sf::Sprite();
        spriteSetting(*stand, *towerStandTexture, 1.);
        stand->setOrigin(250, 250);

        int positionX = towerStandsPositions[i][0];
        int positionY = towerStandsPositions[i][1];
        stand->setPosition(positionX, positionY);

        towerStands.push_back(stand);
    }
}

void Level::deleteTower(Tower* towerToDelete){
    auto it = std::find(towers.begin(), towers.end(), towerToDelete);
    if (it != towers.end()) {
        delete *it;
        towers.erase(it);
    }
}

void Level::createTower(int code, sf::Sprite &stand){
    Tower *tower = new Tower(mainMenu, code);
    towers.push_back(tower);
    tower->setPosition(stand.getPosition().x - 75, stand.getPosition().y - 150);
    stand.setPosition(-1000, -1000);
    sf::Vector2f center = getCenter(tower->getSprite());
    tower->setShootingRadius(tower->getRange(), center, 50);
}

void Level::createHero(int code){
    hero = new Hero(mainMenu, *this, code);
}


void Level::upgradeTower(Tower* tower, int code){
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), code, 0);
    spriteSetting(tower->getSprite(), *texture, .3);
    tower->setValues(mainMenu.getTowerStatsMatrix(), code);
    sf::Vector2f center = getCenter(tower->getSprite());
    tower->setShootingRadius(tower->getRange(), center, 50);
    tower->setCode(code);
    updateMoney(tower->getCost());
}

void Level::handleUpgradeTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgrade, Tower* tower) {
    if(mousePos.x >= towerUpgrade.getPosition().x + 98 && mousePos.x <= towerUpgrade.getPosition().x + 163){
        if(mousePos.y <= towerUpgrade.getPosition().y + 73 && mousePos.y >= towerUpgrade.getPosition().y)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 1);
                closeAllUpgradeMenus();
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
                isRadiusVisible = false;
            }
        if(mousePos.y >= towerUpgrade.getPosition().y + 180 && mousePos.y <= towerUpgrade.getPosition().y + 250){
            updateMoney(-(int)(tower->getApsoluteCost() * .7));
            deleteTower(tower);
            closeAllUpgradeMenus();
            isRadiusVisible = false;
        }
    }
}


void Level::handleUpgradeSplitTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgradeSplit, Tower* tower){
    if(mousePos.y >= towerUpgradeSplit.getPosition().y + 0 && mousePos.y <= towerUpgradeSplit.getPosition().y + 100){
        if(mousePos.x >= towerUpgradeSplit.getPosition().x + 0 && mousePos.x <= towerUpgradeSplit.getPosition().x + 100)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 1);
                towerUpgradeSplit.setPosition(-1000, -1000);
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
                isRadiusVisible = false;
            }
        if(mousePos.x >= towerUpgradeSplit.getPosition().x + 150 && mousePos.x <= towerUpgradeSplit.getPosition().x + 235)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 2);
                towerUpgradeSplit.setPosition(-1000, -1000);
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
                isRadiusVisible = false;
            }
    }
    else if(mousePos.y >= towerUpgradeSplit.getPosition().y + 184 && mousePos.y <= towerUpgradeSplit.getPosition().y + 261)       
        if(mousePos.x >= towerUpgradeSplit.getPosition().x + 98 && mousePos.x <= towerUpgradeSplit.getPosition().x + 163){
            updateMoney(-(int)(tower->getApsoluteCost() * .7));
            deleteTower(tower);
            towerUpgradeSplit.setPosition(-1000, -1000);
            isRadiusVisible = false;
        }
}


void Level::handleAbilityUpgradeTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerAbilityUpgrade, Tower* tower){
    if(mousePos.y >= towerAbilityUpgrade.getPosition().y + 0 && mousePos.y <= towerAbilityUpgrade.getPosition().y + 70){
        if(mousePos.x >= towerAbilityUpgrade.getPosition().x + 24 && mousePos.x <= towerAbilityUpgrade.getPosition().x + 89)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 1);
                towerAbilityUpgrade.setPosition(-1000, -1000);
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
                isRadiusVisible = false;
            }
        if(mousePos.x >= towerAbilityUpgrade.getPosition().x + 170 && mousePos.x <= towerAbilityUpgrade.getPosition().x + 235)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 2);
                towerAbilityUpgrade.setPosition(-1000, -1000);
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
                isRadiusVisible = false;
            }
    }
    else if(mousePos.y >= towerAbilityUpgrade.getPosition().y + 184 && mousePos.y <= towerAbilityUpgrade.getPosition().y + 261)       
        if(mousePos.x >= towerAbilityUpgrade.getPosition().x + 98 && mousePos.x <= towerAbilityUpgrade.getPosition().x + 163){
            updateMoney(-(int)(tower->getApsoluteCost() * .7));
            deleteTower(tower);
            towerAbilityUpgrade.setPosition(-1000, -1000);
            isRadiusVisible = false;
        }
}

void Level::updateMoney(int price){
    setMoney(getMoney() - price);
    ss.str("");
    ss << getMoney();
    moneyText.setString(ss.str());
}

sf::Vector2f getCenter(sf::Sprite sprite){
    sf::Vector2f temp;
    temp.x = sprite.getPosition().x + sprite.getLocalBounds().width * .3 / 2.;
    temp.y = sprite.getPosition().y + sprite.getLocalBounds().height * .3 / 2.;
    return temp;
}

void Level::closeAllUpgradeMenus() {
    towerUpgrade.setPosition(-1000, -1000);
    towerUpgradeSplit.setPosition(-1000, -1000);
    towerAbilityUpgrade.setPosition(-1000, -1000);
    isTowerUpgradeOpen = false;
    isTowerUpgradeSplitOpen = false;
    isAbilityUpgradeOpen = false;
    isRadiusVisible = false;
}

void Level::openTowerUpgradeMenu(Tower* tower) {
    closeAllUpgradeMenus(); 
    towerUpgrade.setPosition(tower->getPosition().x - 60, tower->getPosition().y - 20);
    radius = tower->getShootRadius();
    isTowerUpgradeOpen = true;
    selectedTower = tower;
    isRadiusVisible = true;
}

void Level::openTowerUpgradeSplitMenu(Tower* tower) {
    closeAllUpgradeMenus();
    towerUpgradeSplit.setPosition(tower->getPosition().x - 60, tower->getPosition().y - 20);
    radius = tower->getShootRadius();
    isTowerUpgradeSplitOpen = true;
    selectedTower = tower;
    isRadiusVisible = true;
}

void Level::openAbilityUpgradeMenu(Tower* tower) {
    closeAllUpgradeMenus();
    towerAbilityUpgrade.setPosition(tower->getPosition().x - 60, tower->getPosition().y - 20);
    radius = tower->getShootRadius();
    isAbilityUpgradeOpen = true;
    selectedTower = tower;
    isRadiusVisible = true;
}

sf::Vector2f Level::getHeroStandPosition(){
    sf::Vector2f newHeroStandPosition;
    newHeroStandPosition.x = heroStandPosition[0];
    newHeroStandPosition.y = heroStandPosition[1];
    return newHeroStandPosition;
}

void Level::performBattle(Hero*& hero, Enemy*& fightingEnemy, std::vector<Enemy*>& enemies) {
    sf::Time elapsedTime = clock.getElapsedTime();
    if (hero->getIsHeroFighting()) {
        hero->performAnimation(hero->getAttackTexture(), sf::milliseconds(hero->getAttackSpeed()));
        fightingEnemy->performAnimation(fightingEnemy->getAttackTexture(), sf::milliseconds(fightingEnemy->getAttackSpeed()));
        if (timeSinceLastHeroAttack >= heroAttackInterval) {
            hero->fighting(fightingEnemy);
            //std::cout << "Hero attacks! Enemy health: " << fightingEnemy->getHealth() << std::endl;
            timeSinceLastHeroAttack = sf::Time::Zero;
        }
        if (timeSinceLastEnemyAttack >= enemyAttackInterval) {
            fightingEnemy->fighting(hero); 
            //std::cout << "Enemy attacks! Hero health: " << hero->getHealth() << std::endl;
            timeSinceLastEnemyAttack = sf::Time::Zero;
        }
        timeSinceLastHeroAttack += elapsedTime;
        timeSinceLastEnemyAttack += elapsedTime;
        if (!hero->getIsHeroAlive()) {
            hero->getSprite().setPosition(-1000, -1000);
            fightingEnemy->setIsEnemyFighting(false);
            hero->setIsHeroFighting(false);
            fightingEnemy->move();
        }
        if (!fightingEnemy->getIsEnemyAlive()) {
            auto it = std::find(enemies.begin(), enemies.end(), fightingEnemy);
            if (it != enemies.end()) {
                updateMoney(-(*it)->getBounty());
                fightingEnemy = nullptr;     
                hero->setIsHeroFighting(false);
                delete *it;
                enemies.erase(it);
            }
        }
    }
    else
        if(fightingEnemy != nullptr)
            fightingEnemy->move();
}
