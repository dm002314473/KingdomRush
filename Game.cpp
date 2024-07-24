#include "Game.h"

Game::Game() : window(sf::VideoMode(1920, 1080), "Kingdom Rush"), currentState(MAIN_MENU), mainMenu(new MainMenu()), level(nullptr) {}

void Game::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (currentState)
            {
            case MAIN_MENU:
                mainMenu->handleEvent(event, *this);
                break;
            case LEVEL:
                level->handleEvent(event, *this);
                break;

            default:
                break;
            }
        }

        switch (currentState)
        {
        case LEVEL:
            level->update();
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
    if (newState == LEVEL)
    {
        delete level;
        level = new Level();
    }
    else if (newState == MAIN_MENU)
    {
        delete level;
        level = nullptr;
    }
    currentState = newState;
}