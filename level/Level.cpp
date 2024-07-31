#include "Level.h"

// Should try to remove the texture variable from class and use texture directly from AllTextureMatrix
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

    sf::Texture *newWaveButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 5000, 0);
    spriteSetting(newWaveButton, *newWaveButtonTexture, 0.2);
    newWaveButton.setPosition(20, 20);

    sf::Texture *pauseButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 37, 0);
    spriteSetting(pauseButton, *pauseButtonTexture, 0.2);
    pauseButton.setPosition(1800, 20);

    sf::Texture *forPauseButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 38, 0);
    spriteSetting(forPauseButton, *forPauseButtonTexture, 0.7);
    forPauseButton.setPosition(-1000, -1000);

    sf::Texture *exitButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 36, 0);
    spriteSetting(exitButton, *exitButtonTexture, 0.2);
    exitButton.setPosition(-500, -500);

    sf::Texture *continueButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 35, 0);
    spriteSetting(continueButton, *continueButtonTexture, 0.2);
    continueButton.setPosition(-500, -500);
}

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Vector2i &mousePos, Game &game, bool &exitLevel)
{
    // Handle creating towers, and starting new waves
    if (newWaveButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        wave++;
        startNewWave(wave);
    }
    if (pauseButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        if(isLevelPaused == true){
            continueButton.setPosition(-500, -500);
            exitButton.setPosition(-500, -500);
            forPauseButton.setPosition(-1000, -1000);
            isLevelPaused = false;
        }
        else{
            forPauseButton.setPosition(960, 540);
            exitButton.setPosition(1060, 540);
            continueButton.setPosition(860, 540);
            isLevelPaused = true;
        }
        pauseButton.setPosition(-500, -500);
    }
    if (exitButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        exitLevel = true;
    }
    if (continueButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        pauseButton.setPosition(1800, 20);
        continueButton.setPosition(-500, -500);
        exitButton.setPosition(-500, -500);
        forPauseButton.setPosition(-1000, -1000);
        isLevelPaused = false;
    }
}

void Level::update()
{
    if(!isLevelPaused){
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
    window.draw(newWaveButton);
    window.draw(forPauseButton);
    window.draw(exitButton);
    window.draw(continueButton);
    window.draw(pauseButton);
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
