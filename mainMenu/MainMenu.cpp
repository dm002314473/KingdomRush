#include "MainMenu.h"


// Check the paths
MainMenu::MainMenu(/*Here paths for .txt files may be accepted if needed*/)
{
    imagesReader(allImagesMatrix);
    enemyStatsReader(enemyStatsMatrix);
    towerStatsReader(towerStatsMatrix);
    textureMatrixFiller(allTexturesMatrix);

    sf::Sprite *newFlag = new sf::Sprite();
    levelFlagTexture = getTexture(allTexturesMatrix, 9998, 0);
    if (levelFlagTexture.getSize().x > 0 && levelFlagTexture.getSize().y > 0)
    {
        levelFlagSprite.setTexture(levelFlagTexture);
        newFlag = &levelFlagSprite;
    }
    else
    {
        std::cerr << "Failed to get valid texture for id 9998, column 0." << std::endl;
    }
    backgroundSprite.setTexture(getTexture(allTexturesMatrix, 9998, 0));
    newFlag->setOrigin(0.5, 0.5);
    newFlag->setScale(0.2, 0.2);
    newFlag->setPosition(300, 300);
    levelFlags.push_back(newFlag);

    sf::Sprite *newFlag2 = new sf::Sprite();
    levelFlagTexture2 = getTexture(allTexturesMatrix, 9998, 0);
    if (levelFlagTexture2.getSize().x > 0 && levelFlagTexture2.getSize().y > 0)
    {
        levelFlagSprite2.setTexture(levelFlagTexture2);
        newFlag2 = &levelFlagSprite2;
    }
    else
    {
        std::cerr << "Failed to get valid texture for id 9998, column 0." << std::endl;
    }
    newFlag2->setOrigin(0.5, 0.5);
    newFlag2->setScale(0.2, 0.2);
    newFlag2->setPosition(450, 400);
    levelFlags.push_back(newFlag2);
}

void MainMenu::textureMatrixFiller(std::vector<Row> &allTexturesMatrix)
{
    allTexturesMatrix.resize(allImagesMatrix.size());

    for (size_t i = 0; i < allImagesMatrix.size(); ++i)
    {
        allTexturesMatrix[i].id = std::stoi(allImagesMatrix[i][0]); // Assuming the first element is the id as string
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

std::vector<std::vector<std::string>> MainMenu::getAllImagesMatrix() { return allImagesMatrix; }
std::vector<std::vector<int>> MainMenu::getEnemyStatsMatrix() { return enemyStatsMatrix; }
std::vector<std::vector<int>> MainMenu::getTowerStatsMatrix() { return towerStatsMatrix; }
std::vector<Row> &MainMenu::getAllTexturesMatrix() { return allTexturesMatrix; }

void MainMenu::handleEvent(sf::Vector2i &mousePos, Game &game)
{
    int levelIndex = 1;
    for (auto &flag : levelFlags)
    {
        if (flag->getGlobalBounds().contains((sf::Vector2f)mousePos))
        {
            // start new level
            game.changeState(LEVEL);
            Level *level = new Level(levelIndex, *this);
            game.setLevel(level);
            break;
        }
        levelIndex++;
    }
}

void MainMenu::render(sf::RenderWindow &window)
{
    sf::Texture texture = getTexture(allTexturesMatrix, 9999, 0);
    if (texture.getSize().x > 0 && texture.getSize().y > 0)
    {
        sf::Sprite newSprite;
        newSprite.setTexture(texture);
        window.draw(newSprite);
    }
    else
    {
        std::cerr << "Failed to get valid texture for id 9999, column 0." << std::endl;
    }
    for (auto &flag : levelFlags)
        window.draw(*flag);
}

sf::Texture MainMenu::getTexture(std::vector<Row> &allTexturesMatrix, int code, int column)
{
    for (const auto &row : allTexturesMatrix)
    {
        if (row.id == code)
        {
            if (column >= 0 && column < (int)(row.textures.size()))
            {
                return row.textures[column];
            }
            else
            {
                std::cerr << "Column index out of bounds." << std::endl;
                return sf::Texture();
            }
        }
    }

    std::cerr << "Row with id " << code << " not found." << std::endl;
    return sf::Texture();
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
    while (std::getline(file, line))
    {
        if (isNumber(line))
        {
            if (!currentRow.empty())
            {
                allImagesMatrix.push_back(currentRow);
                currentRow.clear();
            }
            currentRow.push_back(line);
        }
        else
        {
            currentRow.push_back(line);
        }
    }
    if (!currentRow.empty())
    {
        allImagesMatrix.push_back(currentRow);
    }

    file.close();
}

bool MainMenu::isNumber(std::string &line)
{
    for (char c : line)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
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
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> currentRow;
        std::string value;
        while (iss >> value)
        {
            if (isNumber(value))
            {
                currentRow.push_back(std::stoi(value));
            }
            else
            {
                std::cerr << "Invalid number: " << value << std::endl;
                return;
            }
        }
        if (!currentRow.empty())
        {
            enemyStatsMatrix.push_back(currentRow);
        }
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
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> currentRow;
        std::string value;
        while (iss >> value)
        {
            if (isNumber(value))
            {
                currentRow.push_back(std::stoi(value));
            }
            else
            {
                std::cerr << "Invalid number: " << value << std::endl;
                return;
            }
        }
        if (!currentRow.empty())
        {
            towerStatsMatrix.push_back(currentRow);
        }
    }

    file.close();
}