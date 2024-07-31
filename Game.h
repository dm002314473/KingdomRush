#pragma once

#include <SFML/Graphics.hpp>
#include "mainMenu/MainMenu.h"
#include "level/Level.h"

enum GameState
{
    MAIN_MENU,
    LEVEL
};

class MainMenu;
class Level;

class Game
{
private:
    sf::RenderWindow window;
    GameState currentState;
    MainMenu *mainMenu;
    Level *level;

public:
    Game();
    void run();
    void changeState(GameState newState);
    void setLevel(Level *newLevel);
    void handleExitLevel(bool &exitLevel);
};
