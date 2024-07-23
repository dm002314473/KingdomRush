#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Kingdom Rush"), currentState(MAIN_MENU), mainMenu(/*imageTXTpath*/), level(nullptr) {}

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
                mainMenu.handleEvent(event, *this);
                break;
            case LEVEL:
                level.handleEvent(event, *this);
                break;

            default:
                break;
            }
        }

        switch (currentState)
        {
        case MAIN_MENU:
            mainMenu.update();
            break;
        case LEVEL:
            level.update();
            break;
        }

        window.clear();
        switch (currentState)
        {
        case MAIN_MENU:
            mainMenu.render(window);
            break;

        case LEVEL:
            level.render(window);
            break;
        default:
            break;
        }
        window.display();
    }
}

void Game::changeState(GameState newState) { currentState = newState; }