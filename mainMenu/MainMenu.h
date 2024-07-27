#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "../Game.h"

struct Row {
    int id;
    std::vector<sf::Texture> textures;
    std::vector<std::string> texturePaths;
    };

class Game;

class MainMenu
{
private:
    sf::Sprite backgroundSprite;
    sf::Sprite levelFlagSprite;
    sf::Texture backgroundTexture;
    sf::Texture levelFlagTexture;
    std::vector<sf::Sprite *> levelFlags;

    std::vector<std::vector<std::string>> allImagesMatrix;
    std::vector<std::vector<int>> enemyStatsMatrix;
    std::vector<std::vector<int>> towerStatsMatrix;
    std::vector<Row> allTexturesMatrix;

    

public:
    MainMenu();
    void imagesReader(std::vector<std::vector<std::string>> &allImagesMatrix);
    void enemyStatsReader(std::vector<std::vector<int>> &enemyStatsMatrix);
    void towerStatsReader(std::vector<std::vector<int>> &towerStatsMatrix);
    bool isNumber(std::string &line);
    void textureMatrixFiller(std::vector<Row> &allTexturesMatrix);
    sf::Texture getTexture(std::vector<Row> &allTexturesMatrix, int code, int column);

    void handleEvent(sf::Vector2i &mousePos, Game &game);
    void render(sf::RenderWindow &window);
};
