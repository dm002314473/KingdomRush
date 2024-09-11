#include "Level.h"

bool isMenuStandClicked(sf::Vector2i &mousePos, sf::Sprite &menuStand);
int whichTowerToCreate(sf::Vector2i &mousePos, sf::Sprite &menuStand);
bool isThereTowerAlready(std::vector<Tower *> &towers, sf::Sprite stand);
void pauseLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused);
void continueLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused);

Level::Level(int levelIndex, MainMenu &MainMenu) : mainMenu(MainMenu), isLevelPaused(false)
{
    std::string levelFile = "GeneralRehearsal\\level\\lvl" + std::to_string(levelIndex) + ".txt";
    readingLevelData(levelFile);
    sf::Texture *backgroundTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), levelIndex, 0);
    levelBackground.setTexture(*backgroundTexture);

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

    setMoney(1000);
    if (!font.loadFromFile("GeneralRehearsal/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf")) {
        return ;
    }
    setTextBox(moneyText, font, moneyBox);
    ss << getMoney();
    moneyText.setString(ss.str());
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
    if (buttons[0]->getGlobalBounds().contains((sf::Vector2f)mousePos)) {
        wave++;
        startNewWave(wave);
    }

    if (isMenuStandOpen && !isMenuStandClicked(mousePos, menuStand)) {
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
    else if (isMenuStandOpen && isMenuStandClicked(mousePos, menuStand)) {
        handleMenuClickEvent(mousePos, menuStand);
    }
     for (auto tower : towers) {
            if (tower->isClicked(mousePos)) {
                if(tower->getCode() % 10000 == 0 || tower->getCode() % 10000 == 1){
                    sf::Texture *towerUpgradeMenuTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), TOWER_UPGRADE, 0);
                    spriteSetting(towerUpgrade, *towerUpgradeMenuTexture, 1.);
                    towerUpgrade.setPosition(tower->getPosition().x - 60, tower->getPosition().y - 20);
                    handleUpgradeTowerClickEvent(mousePos, towerUpgrade, tower);
                    break;
                }
                else if(tower->getCode() % 10000 == 2){
                    sf::Texture *towerUpgradeSplitMenuTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), TOWER_UPGRADE_SPLIT, 0);
                    spriteSetting(towerUpgradeSplit, *towerUpgradeSplitMenuTexture, 1.);
                    towerUpgradeSplit.setPosition(tower->getPosition().x - 60, tower->getPosition().y - 20);
                    handleUpgradeSplitTowerClickEvent(mousePos, towerUpgradeSplit, tower);
                    break;
                }
                else{
                    //upgrade abilities
                    sf::Texture *towerUpgradeMenuTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), TOWER_UPGRADE, 0);
                    spriteSetting(towerUpgrade, *towerUpgradeMenuTexture, 1.);
                    towerUpgrade.setPosition(tower->getPosition().x - 60, tower->getPosition().y - 20);
                    handleUpgradeTowerClickEvent(mousePos, towerUpgrade, tower);
                    break;
                }
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
            updateMoney(100);
        }
        break;
    case 2:
        if (getMoney() >= 70)
        {
            createTower(ARC_LVL1, menuStand);
            menuStand.setPosition(-1000, -1000);
            updateMoney(70);
        }
        break;
    case 3:
        if (getMoney() >= 70)
        {
            createTower(BARRACKS_LVL1, menuStand);
            menuStand.setPosition(-1000, -1000);
            updateMoney(70);
        }
        break;
    case 4:
        if (getMoney() >= 120)
        {
            createTower(BOMBARD_LVL1, menuStand);    
            menuStand.setPosition(-1000, -1000);
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

bool isMenuStandClicked(sf::Vector2i &mousePos, sf::Sprite &menuStand)
{
    if (isButtonClicked(menuStand, mousePos))
        return true;
    return false;
}

void Level::update()
{
    if (isLevelPaused)
        return;

    for (auto it = enemies.begin(); it != enemies.end();)
    {
        (*it)->move();
        if ((*it)->isOutOfMap())
        {
            delete *it;
            it = enemies.erase(it);
        }
        else
            ++it;
    }
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
    window.draw(moneyBox);
    window.draw(moneyText);
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
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        iss >> word;
        if (word == "waypoints" || word == "tower" || word == "hero")
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
            else
                heroStandPosition = position;
        }
    }
    file.close();
}

void Level::startNewWave(int waveIndex)
{
    for (int i = 0; i < 5; i++)
    {
        Enemy *enemy = new Enemy(mainMenu, waypoints);
        enemies.push_back(enemy);
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

void Level::createTower(int code, sf::Sprite &stand){
    Tower *tower = new Tower(mainMenu, code);
    towers.push_back(tower);
    tower->setPosition(stand.getPosition().x - 75, stand.getPosition().y - 150);
    stand.setPosition(-1000, -1000);
}

void Level::handleUpgradeTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgrade, Tower* tower) {
    if(mousePos.x >= towerUpgrade.getPosition().x + 98 && mousePos.x <= towerUpgrade.getPosition().x + 163){
        if(mousePos.y <= towerUpgrade.getPosition().y + 73 && mousePos.y >= towerUpgrade.getPosition().y)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 1);
                towerUpgrade.setPosition(-1000, -1000);
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
            }
        if(mousePos.y >= towerUpgrade.getPosition().y + 180 && mousePos.y <= towerUpgrade.getPosition().y + 250){
            updateMoney(-(int)(tower->getApsoluteCost() * .7));
            deleteTower();
            towerUpgrade.setPosition(-1000, -1000);
        }
    }
}

void Level::deleteTower(){
    for (auto it = towers.begin(); it != towers.end();)
    {
        if ((*it)->getPosition().x - 60 == towerUpgrade.getPosition().x && (*it)->getPosition().y - 20 == towerUpgrade.getPosition().y)
        {
            delete *it;
            it = towers.erase(it);
        }
        else
            ++it;
    }
}


void Level::upgradeTower(Tower* tower, int code){
    sf::Texture *texture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), code, 0);
    spriteSetting(tower->getSprite(), *texture, .3);
    tower->setValues(mainMenu.getTowerStatsMatrix(), code);
    tower->setCode(code);
    updateMoney(tower->getCost());
}

void Level::handleUpgradeSplitTowerClickEvent(sf::Vector2i &mousePos, sf::Sprite &towerUpgradeSplit, Tower* tower){
    if(mousePos.y >= towerUpgradeSplit.getPosition().y + 0 && mousePos.y <= towerUpgradeSplit.getPosition().y + 70){
        if(mousePos.x >= towerUpgradeSplit.getPosition().x + 24 && mousePos.x <= towerUpgradeSplit.getPosition().x + 89)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 1);
                towerUpgradeSplit.setPosition(-1000, -1000);
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
            }
        else if(mousePos.x >= towerUpgradeSplit.getPosition().x + 170 && mousePos.x <= towerUpgradeSplit.getPosition().x + 235)
            if(getMoney() >= tower->getNextLevelCost()){
                upgradeTower(tower, tower->getCode() + 2);
                towerUpgradeSplit.setPosition(-1000, -1000);
                tower->setApsoluteCost(tower->getApsoluteCost() + tower->getCost());
            }
    }
    else if(mousePos.y >= towerUpgradeSplit.getPosition().y + 184 && mousePos.y <= towerUpgradeSplit.getPosition().y + 261)       
        if(mousePos.x >= towerUpgradeSplit.getPosition().x + 98 && mousePos.x <= towerUpgrade.getPosition().x + 163){
            updateMoney(-(int)(tower->getApsoluteCost() * .7));
            deleteTower();
            towerUpgrade.setPosition(-1000, -1000);
        }
}

void Level::updateMoney(int price){
    setMoney(getMoney() - price);
    ss.str("");
    ss << getMoney();
    moneyText.setString(ss.str());
}