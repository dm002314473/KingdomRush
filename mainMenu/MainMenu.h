#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "../Game.h"
#include "../commonFunctions/CommonFunctions.h"

struct Row
{
    int id;
    std::vector<sf::Texture> textures;
    std::vector<std::string> texturePaths;
};

class Game;

class MainMenu
{
private:
    sf::Texture *backgroundTexture;
    sf::Sprite *backgroundSprite;

    sf::Texture *exitButtonTexture;
    sf::Sprite *exitButton;

    sf::Texture *levelFlagTexture;
    std::vector<sf::Sprite *> levelFlagSprites;

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
    sf::Texture *getTexturePtr(std::vector<Row> &allTexturesMatrix, int code, int column);

    std::vector<std::vector<std::string>> getAllImagesMatrix();
    std::vector<std::vector<int>> getEnemyStatsMatrix();
    std::vector<std::vector<int>> getTowerStatsMatrix();
    std::vector<Row> &getAllTexturesMatrix();

    void handleEvent(sf::Vector2i &mousePos, Game &game, sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
};
