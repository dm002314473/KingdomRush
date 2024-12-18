#include "MainMenu.h"

MainMenu::MainMenu()
{
    imagesReader(allImagesMatrix);
    enemyStatsReader(enemyStatsMatrix);
    towerStatsReader(towerStatsMatrix);
    textureMatrixFiller(allTexturesMatrix);

    exitButton = new sf::Sprite();
    exitButtonTexture = getTexturePtr(allTexturesMatrix, EXIT, 0);

    if (exitButtonTexture->getSize().x > 0 && exitButtonTexture->getSize().y > 0)
    {
        spriteSetting(*exitButton, *exitButtonTexture, 0.3);
        exitButton->setPosition(1700, 20);
    }
    else
        std::cerr << "Failed to get valid texture for id 9998, column 0." << std::endl;

    levelFlagTexture = getTexturePtr(allTexturesMatrix, FLAG_FOR_LVL, 0);
    for (int i = 0; i < 3; i++)
    {
        if (levelFlagTexture->getSize().x > 0 && levelFlagTexture->getSize().y > 0)
        {
            sf::Sprite *newFlag = new sf::Sprite();
            spriteSetting(*newFlag, *levelFlagTexture, 0.2);
            newFlag->setPosition(300 + i * 100, 300 + i * 100);
            levelFlagSprites.push_back(newFlag);
        }
        else
        {
            std::cerr << "Failed to get valid texture for id FLAG_FOR_LVL, column 0." << std::endl;
        }
    }

    backgroundSprite = new sf::Sprite();
    backgroundTexture = getTexturePtr(allTexturesMatrix, MAIN_MAP, 0);
    spriteSetting(*backgroundSprite, *backgroundTexture, 1);
}

std::vector<std::vector<std::string>> MainMenu::getAllImagesMatrix() { return allImagesMatrix; }
std::vector<std::vector<int>> MainMenu::getEnemyStatsMatrix() { return enemyStatsMatrix; }
std::vector<std::vector<int>> MainMenu::getTowerStatsMatrix() { return towerStatsMatrix; }
std::vector<Row> &MainMenu::getAllTexturesMatrix() { return allTexturesMatrix; }

void MainMenu::handleEvent(sf::Vector2i &mousePos, Game &game, sf::RenderWindow &window)
{
    int levelIndex = 1;
    for (auto &flag : levelFlagSprites)
    {
        if (isButtonClicked(*flag, mousePos))
        {
            // start new level
            game.changeState(LEVEL);
            Level *level = new Level(levelIndex, *this);
            game.setLevel(level);
            break;
        }
        levelIndex++;
    }
    if (isButtonClicked(*exitButton, mousePos))
        window.close();
}

void MainMenu::render(sf::RenderWindow &window)
{
    window.draw(*backgroundSprite);

    for (auto &flag : levelFlagSprites)
        window.draw(*flag);

    window.draw(*exitButton);
}

sf::Texture *MainMenu::getTexturePtr(std::vector<Row> &allTexturesMatrix, int code, int column)
{
    for (auto &row : allTexturesMatrix)
    {
        if (row.id == code && column < row.textures.size())
            return &row.textures[column];
    }
    return nullptr;
}

void MainMenu::textureMatrixFiller(std::vector<Row> &allTexturesMatrix)
{
    allTexturesMatrix.resize(allImagesMatrix.size());

    for (size_t i = 0; i < allImagesMatrix.size(); ++i)
    {
        allTexturesMatrix[i].id = std::stoi(allImagesMatrix[i][0]);
        allTexturesMatrix[i].textures.resize(allImagesMatrix[i].size() - 1);
        allTexturesMatrix[i].texturePaths.resize(allImagesMatrix[i].size() - 1);

        for (size_t j = 1; j < allImagesMatrix[i].size(); ++j)
        {
            if (!allTexturesMatrix[i].textures[j - 1].loadFromFile(allImagesMatrix[i][j]))
                std::cerr << "Failed to load " << allImagesMatrix[i][j] << std::endl;
            else
                allTexturesMatrix[i].texturePaths[j - 1] = allImagesMatrix[i][j];
        }
    }
}

void MainMenu::imagesReader(std::vector<std::vector<std::string>> &allImagesMatrix)
{
    std::ifstream file("GeneralRehearsal\\mainMenu\\imagesPaths.txt");
    if (!file.is_open())
    {
        std::cerr << "Unable to open imagesPaths.txt" << std::endl;
        return;
    }
    std::vector<std::string> currentRow;
    std::string line;
    
    while (std::getline(file, line)) {
        if (isNumber(line)) {
            if (!currentRow.empty()) {
                allImagesMatrix.push_back(currentRow);
                currentRow.clear();
            }
            currentRow.push_back(line);
        } else {
            currentRow.push_back(line);
        }
    }
    
    if (!currentRow.empty()) {
        allImagesMatrix.push_back(currentRow);
    }

    file.close();
}

bool MainMenu::isNumber(std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void MainMenu::enemyStatsReader(std::vector<std::vector<int>> &enemyStatsMatrix)
{
    std::ifstream file("GeneralRehearsal\\mainMenu\\enemyStats.txt");
    if (!file.is_open())
    {
        std::cerr << "Unable to open enemyStats.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int num;
        int count = 0;
        while (iss >> num) {
            row.push_back(num);
            count++;
        }
        if (count != 11) {
            std::cerr << "Line does not contain exactly 11 numbers: " << line << std::endl;
            continue;
        }

        enemyStatsMatrix.push_back(row);
    }
    
    file.close();
}

void MainMenu::towerStatsReader(std::vector<std::vector<int>> &towerStatsMatrix)
{
    std::ifstream file("GeneralRehearsal\\mainMenu\\towerStats.txt");
    if (!file.is_open())
    {
        std::cerr << "Unable to open towerStats.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int num;
        int count = 0;
        while (iss >> num) {
            row.push_back(num);
            count++;
        }
        if (count != 7) {
            std::cerr << "Line does not contain exactly 7 numbers: " << line << std::endl;
            continue; 
        }

        towerStatsMatrix.push_back(row);
    }
    
    file.close();
}