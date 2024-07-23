#include <SFML/Graphics.hpp>
#include "mainMenu/MainMenu.h"

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
    MainMenu mainMenu;
    // Level level;

    void processEvents();
    void update();
    void render();

public:
    Game(std::string mainMenuDocumentPath);
    void run();
};
