#include "Level.h"

// Should try to remove the texture variable from class and use texture directly from AllTextureMatrix
Level::Level(int levelIndex, MainMenu &mainMenu)
{
    std::string levelFile = "GeneralRehearsal\\level\\lvl" + std::to_string(levelIndex) + ".txt";
    readingLevelData(levelFile);

    backgroundTexture = mainMenu.getTexture(mainMenu.getAllTexturesMatrix(), levelIndex, 0);

    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        levelBackground.setTexture(backgroundTexture);
    }
    else
        std::cerr << "Failed to get valid texture." << std::endl;
}

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Event &event, Game &game)
{
    // Handle creating towers, and starting new waves
    /*
    if (towerStandClicked)
        handleTowerStandClick()
    else if (startWaveButtonClicked)
        handleStartWaveButtonClick()
    */
}

void Level::update()
{
    // Implement logic for enemy movement and tower shooting
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
}


void Level::readingLevelData(std::string &levelTxtFile){
    std::ifstream file(levelTxtFile);
    if (!file.is_open())
    {
        std::cerr << "Unable to open " << levelTxtFile << std::endl;
        return;
    }
    std::vector<std::string> currentRow;
    std::string line;
    std::string currentState;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        iss >> word;
        if (word == "waypoints" || word == "tower" || word == "hero")
            currentState = word;
        else{
            std::istringstream iss(line);
            int x, y;
            char comma;
            iss.seekg(0);
            iss >> x >> comma >> y;
            if (comma != ',') {
                std::cerr << "Error: Expected comma between coordinates." << std::endl;
                continue;
            }
            std::vector<int> position = {x, y};
            if (currentState == "waypoints")
                waypoints.push_back(position);
            else if(currentState == "tower")
                towerStandsPositions.push_back(position);
            else
                heroStandPosition = position;    
        }
    }

    file.close();
}