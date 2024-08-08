#include "Level.h"

void handleMenuClickEvent(sf::Vector2i &mousePos, sf::Sprite &menuStand);
void pauseLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused);
void continueLevel(std::vector<sf::Sprite *> buttons, bool &isLevelPaused);
bool isMenuStandClicked(sf::Vector2i &mousePos, sf::Sprite &menuStand);
int whichTowerToCreate(sf::Vector2i &mousePos, sf::Sprite &menuStand);

Level::Level(int levelIndex, MainMenu &MainMenu) : mainMenu(MainMenu), isLevelPaused(false)
{
    std::string levelFile = "GeneralRehearsal\\level\\lvl" + std::to_string(levelIndex) + ".txt";
    readingLevelData(levelFile);
    sf::Texture *backgroundTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), levelIndex, 0);
    levelBackground.setTexture(*backgroundTexture);

    int polje[5][2] = {{20, 20}, {1800, 20}, {-1000, -1000}, {-500, -500}, {-500, -500}};
    int sifre[5] = {5000, 37, 38, 36, 35};

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
}

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Vector2i &mousePos, Game &game, bool &exitLevel)
{
    if (isButtonClicked(*buttons[0], mousePos))
    {
        wave++;
        startNewWave(wave);
    }
    if (isButtonClicked(*buttons[1], mousePos))
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

    if (isMenuStandOpen && !isMenuStandClicked(mousePos, menuStand))
    {
        isMenuStandOpen = false;
        menuStand.setPosition(-1000, -1000);
    }
    if (!isMenuStandOpen)
    {
        for (auto stand : towerStands)
            if (isButtonClicked(*stand, mousePos))
            {
                menuStand.setPosition(stand->getPosition().x - 178, stand->getPosition().y - 202);
                isMenuStandOpen = true;
                break;
            }
    }
    else if (isMenuStandOpen && isMenuStandClicked(mousePos, menuStand))
        handleMenuClickEvent(mousePos, menuStand);
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

void handleMenuClickEvent(sf::Vector2i &mousePos, sf::Sprite &menuStand)
{
    int towerMark = whichTowerToCreate(mousePos, menuStand);
    switch (towerMark)
    {
    case 1:
        std::cout << "wiz" << std::endl;
        menuStand.setPosition(-1000, -1000);
        break;
    case 2:
        std::cout << "arc" << std::endl;
        menuStand.setPosition(-1000, -1000);
        break;
    case 3:
        std::cout << "baraka" << std::endl;
        menuStand.setPosition(-1000, -1000);
        break;
    case 4:
        std::cout << "bombar" << std::endl;
        menuStand.setPosition(-1000, -1000);
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
    // menuStand.getGlobalBounds().contains((sf::Vector2f)mousePos)
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
    // Implement logic for tower shooting
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
