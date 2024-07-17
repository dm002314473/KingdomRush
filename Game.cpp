#include "Game.h"

Game::Game(std::string mainMenuDocumentPath) : window(sf::VideoMode(1920, 1080), "Generalka"), currentState(MAIN_MENU), mainMenu(mainMenuDocumentPath) {}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        switch (currentState)
        {
        case MAIN_MENU:
            mainMenu.handleEvent(event);
            break;
        // case LEVEL:
        //     level.handleEvent(event);
        //     break;
        default:
            break;
        }
    }
}

void Game::update() {}

void Game::render() {}