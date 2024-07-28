#include "Level.h"

// Should try to remove the texture variable from class and use texture directly from AllTextureMatrix
Level::Level(int levelIndex, MainMenu &MainMenu) : mainMenu(MainMenu)
{
    std::string levelFile = "GeneralRehearsal\\level\\lvl" + std::to_string(levelIndex) + ".txt";
    readingLevelData(levelFile);
    sf::Texture *backgroundTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), levelIndex, 0);
    if (backgroundTexture && backgroundTexture->getSize().x > 0 && backgroundTexture->getSize().y > 0)
    {
        levelBackground.setTexture(*backgroundTexture);
        std::cout << "Loaded sprite" << std::endl;
    }
    else
        std::cerr << "Failed to get valid texture." << std::endl;

    sf::Texture *newWaveButtonTexture = mainMenu.getTexturePtr(mainMenu.getAllTexturesMatrix(), 5000, 0);
    newWaveButton.setTexture(*newWaveButtonTexture);
    newWaveButton.setPosition(20, 20);
    newWaveButton.setScale(0.2, 0.2);
}

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Vector2i &mousePos, Game &game)
{
    // Handle creating towers, and starting new waves
    if (newWaveButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
    {

        // newWave
        wave++;
        startNewWave(wave);
    }
}

void Level::update()
{
    for (auto &enemy : enemies)
        enemy->move();
    // Implement logic for tower shooting
}

void Level::render(sf::RenderWindow &window)
{
    window.draw(levelBackground);
    window.draw(newWaveButton);
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

void Level::startNewWave(int waveIndex)
{
    for (int i = 0; i < 5; i++){
        Enemy *enemy = new Enemy(mainMenu, waypoints);       
        enemies.push_back(enemy);
    }
}
