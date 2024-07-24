#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "../Game.h"

class Game;

class MainMenu
{
private:
    sf::Sprite backgroundSprite;
    std::vector<sf::Sprite *> towerStands;

    std::vector<std::vector<std::string>> allImagesMatrix;
    std::vector<std::vector<int>> enemyStatsMatrix;
    std::vector<std::vector<int>> towerStatsMatrix;
    std::vector<std::vector<sf::Texture>> allTexturesMatrix;

public:
    MainMenu();
    void imagesReader(std::vector<std::vector<std::string>> &allImagesMatrix);
    void enemyStatsReader(std::vector<std::vector<int>> &enemyStatsMatrix);
    void towerStatsReader(std::vector<std::vector<int>> &towerStatsMatrix);
    bool isNumber(std::string &line);
    void textureMatrixFiller(std::vector<std::vector<sf::Texture>> &allTexturesMatrix);

    void handleEvent(sf::Event &event, Game &game);
    void render(sf::RenderWindow &window);
};
