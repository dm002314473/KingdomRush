#include "MainMenu.h"

MainMenu::MainMenu(std::string mainMenuDocumentPath) : mainMenuDocumentPath(mainMenuDocumentPath)
{
    // procitat sve pathove za level.txtove i spremit u levelDocumentPaths

    std::string pathToMainMenuBackground = ""; // procitat iz mainmenu.txt
    if (!texture.loadFromFile(pathToMainMenuBackground))
    {
        std::cerr << "Unable to load mainMenuBackground.png" << std::endl;
    }

    sprite.setTexture(texture);
}

void MainMenu::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < levelFlags.size(); i++)
            {
                if (levelFlags[i]->getGlobalBounds().contains(mousePosition))
                {
                    std::cout << "LevelFlag clicked!" << std::endl;
                    // Start the specific level here
                    Level::loadLevel(i);
                }
            }
        }
    }
}
