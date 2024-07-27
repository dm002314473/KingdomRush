#include "MainMenu.h"

void MainMenu::textureMatrixFiller(std::vector<Row> &allTexturesMatrix)
{
    allTexturesMatrix.resize(allImagesMatrix.size());

    for (size_t i = 0; i < allImagesMatrix.size(); ++i) {
        allTexturesMatrix[i].id = std::stoi(allImagesMatrix[i][0]); // Assuming the first element is the id as string
        allTexturesMatrix[i].textures.resize(allImagesMatrix[i].size() - 1);
        allTexturesMatrix[i].texturePaths.resize(allImagesMatrix[i].size() - 1);

        for (size_t j = 1; j < allImagesMatrix[i].size(); ++j) {
            if (!allTexturesMatrix[i].textures[j - 1].loadFromFile(allImagesMatrix[i][j])) {
                std::cerr << "Failed to load " << allImagesMatrix[i][j] << std::endl;
            } else {
                allTexturesMatrix[i].texturePaths[j - 1] = allImagesMatrix[i][j];
            }
        }
    }
}

// Check the paths
MainMenu::MainMenu(/*Here paths for .txt files may be accepted if needed*/)
{
    imagesReader(allImagesMatrix);
    enemyStatsReader(enemyStatsMatrix);
    towerStatsReader(towerStatsMatrix);
    textureMatrixFiller(allTexturesMatrix);
    sf::Sprite* newFlag = new sf::Sprite ();
    levelFlagTexture = getTexture(allTexturesMatrix, 9998, 0);
    if (levelFlagTexture.getSize().x > 0 && levelFlagTexture.getSize().y > 0) {    
        levelFlagSprite.setTexture(levelFlagTexture);
        newFlag = &levelFlagSprite;
    } else {
        std::cerr << "Failed to get valid texture for id 9998, column 0." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    newFlag->setOrigin(0.5, 0.5);
    newFlag->setScale(0.2, 0.2);
    levelFlags.push_back(newFlag);
    levelFlags.push_back(newFlag);
    std::cout << std:: endl << "MainMenu constructor reached!" << std::endl;
}

void MainMenu::handleEvent(sf::Vector2i &mousePos, Game &game)
{
    for (auto &flag : levelFlags)
    {
        if (flag->getGlobalBounds().contains((sf::Vector2f)mousePos))
        {
            std::cout << "Mouse clicked on Level Flag" << std::endl;
            // start new level
            game.changeState(LEVEL);
            int levelIndex = 1 /* some logic to determine which level this flag represents */;
            Level *level = new Level(levelIndex);
            game.setLevel(level);
            break;
        }
    }
}

void MainMenu::render(sf::RenderWindow &window)
{
    sf::Texture texture = getTexture(allTexturesMatrix, 9999, 0);
    if (texture.getSize().x > 0 && texture.getSize().y > 0) {
        sf::Sprite newSprite;
        newSprite.setTexture(texture);
        window.draw(newSprite);
    } else {
        std::cerr << "Failed to get valid texture for id 9999, column 0." << std::endl;
    }
    for (auto &flag : levelFlags)
    {
        flag->setPosition(300, 300);
        window.draw(*flag);
    }
}



sf::Texture MainMenu::getTexture(std::vector<Row> &allTexturesMatrix, int code, int column){
     for (const auto& row : allTexturesMatrix) {
        if (row.id == code) {
            if (column >= 0 && column < (int)(row.textures.size())) {
                return row.textures[column];
            } else {
                std::cerr << "Column index out of bounds." << std::endl;
                return sf::Texture();
            }
        }
    }

    std::cerr << "Row with id " << code << " not found." << std::endl;
    return sf::Texture();
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