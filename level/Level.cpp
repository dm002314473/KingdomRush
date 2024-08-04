#include "Level.h"

Level::Level(int levelIndex, MainMenu &MainMenu) : mainMenu(MainMenu)
{
    isLevelPaused = false;
    std::string levelFile = "GeneralRehearsal\\level\\lvl" + std::to_string(levelIndex) + ".txt";
    readingLevelData(levelFile);
    sf::Texture *backgroundTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), levelIndex, 0);
    if (backgroundTexture && backgroundTexture->getSize().x > 0 && backgroundTexture->getSize().y > 0)
        levelBackground.setTexture(*backgroundTexture);
    else
        std::cerr << "Failed to get valid texture." << std::endl;

    // sf::Texture *newWaveButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 5000, 0);
    // spriteSetting(newWaveButton, *newWaveButtonTexture, 0.2);
    // newWaveButton.setPosition(20, 20);

    // sf::Texture *pauseButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 37, 0);
    // spriteSetting(pauseButton, *pauseButtonTexture, 0.2);
    // pauseButton.setPosition(1800, 20);

    // sf::Texture *forPauseButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 38, 0);
    // spriteSetting(forPauseButton, *forPauseButtonTexture, 0.7);
    // forPauseButton.setPosition(-1000, -1000);

    // sf::Texture *exitButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 36, 0);
    // spriteSetting(exitButton, *exitButtonTexture, 0.2);
    // exitButton.setPosition(-500, -500);

    // sf::Texture *continueButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 35, 0);
    // spriteSetting(continueButton, *continueButtonTexture, 0.2);
    // continueButton.setPosition(-500, -500);

    int polje[5][2] = {{20, 20}, {1800, 20}, {-1000, -1000}, {-500, -500}, {-500, 500}};
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
}

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Vector2i &mousePos, Game &game, bool &exitLevel)
{
    // Handle creating towers, and starting new waves
    if (buttons[0]->getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        wave++;
        startNewWave(wave);
    }
    if (buttons[1]->getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        if (isLevelPaused == true)
        {
            buttons[4]->setPosition(-500, -500);
            buttons[3]->setPosition(-500, -500);
            buttons[2]->setPosition(-1000, -1000);
            isLevelPaused = false;
        }
        else
        {
            buttons[2]->setPosition(960, 540);
            buttons[3]->setPosition(1060, 540);
            buttons[4]->setPosition(860, 540);
            isLevelPaused = true;
        }
        buttons[1]->setPosition(-500, -500);
    }
    if (buttons[3]->getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        exitLevel = true;
    }
    if (buttons[4]->getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        buttons[1]->setPosition(1800, 20);
        buttons[4]->setPosition(-500, -500);
        buttons[3]->setPosition(-500, -500);
        buttons[2]->setPosition(-1000, -1000);
        isLevelPaused = false;
    }
}

void Level::update()
{
    if (!isLevelPaused)
    {
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
    }
    // Implement logic for tower shooting
}

void Level::render(sf::RenderWindow &window)
{
    window.draw(levelBackground);
    for (auto &enemy : enemies)
        window.draw(enemy->getSprite());
    for (auto &tower : towers)
        window.draw(tower->getSprite());
    for (auto &towerStand : towerStands)
        window.draw(*towerStand);
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

void Level::settingTowerStands(){
    sf::Texture *towerStandTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 10000, 0);
    for (auto stand : towerStands) {
        delete stand;
    }
    towerStands.clear();
    
    for (size_t i = 0; i < towerStandsPositions.size(); i++) {
        sf::Sprite *stand = new sf::Sprite();
        spriteSetting(*stand, *towerStandTexture, 1.);
        stand->setOrigin(250, 250);

        int positionX = towerStandsPositions[i][0];
        int positionY = towerStandsPositions[i][1];
        stand->setPosition(positionX, positionY);

        towerStands.push_back(stand);
    }
}