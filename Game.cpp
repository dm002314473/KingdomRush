#include "Game.h"

Game::Game() : window(sf::VideoMode(1920, 1080), "Kingdom Rush"), currentState(MAIN_MENU), mainMenu(new MainMenu()), level(nullptr) {}

void Game::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        bool exitLevel = false;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (currentState)
            {
            case MAIN_MENU:
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    mainMenu->handleEvent(mousePos, *this);
                }
                break;
            case LEVEL:
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    level->handleEvent(mousePos, *this, exitLevel);
                }
                break;

            default:
                break;
            }
        }
        if (exitLevel)
        {
            delete level;
            level = nullptr;
            changeState(MAIN_MENU);
            continue;
        }

        switch (currentState)
        {
        case LEVEL:
            level->update();
            break;
        default:
            break;
        }
        window.clear();
        switch (currentState)
        {
        case MAIN_MENU:
            mainMenu->render(window);
            break;

        case LEVEL:
            level->render(window);
            break;
        default:
            break;
        }
        window.display();
    }
}

void Game::changeState(GameState newState)
{
    delete level;
    level = nullptr;

    currentState = newState;
}

void Game::setLevel(Level *newLevel) { level = newLevel; }