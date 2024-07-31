#include "Game.h"

void handlePoolEventMainMenu(sf::Event &event, sf::RenderWindow &window, MainMenu *mainMenu, Game &game);
void handlePoolEventLevel(sf::Event &event, sf::RenderWindow &window, Level *level, bool &exitLevel, Game &game);

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

            // Handling click events
            switch (currentState)
            {
            case MAIN_MENU:
                handlePoolEventMainMenu(event, window, mainMenu, *this);
                break;
            case LEVEL:
                handlePoolEventLevel(event, window, level, exitLevel, *this);
                break;
            default:
                break;
            }
        }
        if (exitLevel)
        {
            handleExitLevel(exitLevel);
            continue;
        }

        // Updating level frame
        switch (currentState)
        {
        case LEVEL:
            level->update();
            break;
        default:
            break;
        }

        // Rendering
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

void handlePoolEventMainMenu(sf::Event &event, sf::RenderWindow &window, MainMenu *mainMenu, Game &game)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mainMenu->handleEvent(mousePos, game);
    }
}

void handlePoolEventLevel(sf::Event &event, sf::RenderWindow &window, Level *level, bool &exitLevel, Game &game)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        level->handleEvent(mousePos, game, exitLevel);
    }
}

void Game::handleExitLevel(bool &exitLevel)
{
    delete level;
    level = nullptr;
    changeState(MAIN_MENU);
}
