#include "MainMenu.h"

void MainMenu::textureMatrixFiller(std::vector<std::vector<sf::Texture>> &allTexturesMatrix)
{
    allTexturesMatrix.resize(allImagesMatrix.size());

    for (size_t i = 0; i < allImagesMatrix.size(); ++i)
    {
        allTexturesMatrix[i].resize(allImagesMatrix[i].size() - 1);

        for (size_t j = 1; j < allImagesMatrix[i].size(); ++j)
        {
            std::cout << "Loading texture from: " << allImagesMatrix[i][j] << std::endl;

            if (!allTexturesMatrix[i][j - 1].loadFromFile(allImagesMatrix[i][j]))
            {
                std::cerr << "Failed to load " << allImagesMatrix[i][j] << std::endl;
            }
        }
    }
}

// Check the paths
MainMenu::MainMenu(/*Here paths for .txt files may be accepted if needed*/)
{
    if (!backgroundTexture.loadFromFile("GeneralRehearsal/images/main_map.png"))
    {
        std::cout << "unable to load GeneralRehearsal/images/main_map.png" << std::endl;
        return;
    }
    if (!levelFlagTexture.loadFromFile("GeneralRehearsal/images/flag_for_lvl.png"))
    {
        std::cout << "unable to load GeneralRehearsal/images/flag_for_lvl.png" << std::endl;
        return;
    }
    // tower stand je zapravo flag for lvl triba postavit njihovo pushbackanje, scale, postavit setorigin
    levelFlagSprite.setTexture(levelFlagTexture);
    sf::Sprite *newStand = new sf::Sprite();
    newStand = &levelFlagSprite;
    newStand->setOrigin(0.5, 0.5);
    newStand->setScale(0.2, 0.2);
    backgroundSprite.setTexture(backgroundTexture);
    imagesReader(allImagesMatrix);
    enemyStatsReader(enemyStatsMatrix);
    towerStatsReader(towerStatsMatrix);
    textureMatrixFiller(allTexturesMatrix);
    levelFlags.push_back(newStand);
    std::cout << "MainMenu constructor reached!" << std::endl;

    // for (int i = 0; i < allImagesMatrix.size(); ++i)
    // {
    //     allTexturesMatrix[i].resize(allImagesMatrix[i].size());
    //     for (size_t j = 0; j < allImagesMatrix[i].size(); ++j)
    //     {
    //         if (!allTexturesMatrix[i][j].loadFromFile(allImagesMatrix[i][j]))
    //         {
    //             std::cerr << "Failed to load " << allImagesMatrix[i][j] << std::endl;
    //         }
    //     }
    // }

    // backgroundSprite.setTexture(allTexturesMatrix[0][0]);
    // for (auto &stand : towerStands)
    //     stand->setTexture(allTexturesMatrix[0][1]);
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
    window.draw(backgroundSprite);
    for (auto &flag : levelFlags)
    {
        flag->setPosition(300, 300);
        window.draw(*flag);
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