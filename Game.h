#pragma once
#include <SFML/Graphics.hpp>

enum GameState
{
    MAIN_MENU,
    LEVEL
};

class Game
{
private:
    sf::RenderWindow window;
    GameState currentState;
    // Level level;

    void processEvents();
    void update();
    void render();

public:
    Game(std::string mainMenuDocumentPath);
    void run();
};
