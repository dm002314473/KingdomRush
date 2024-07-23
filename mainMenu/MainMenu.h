#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class MainMenu
{
private:
    std::vector<std::vector<std::string>> allImagesMatrix;
    std::vector<std::vector<int>> enemyStatsMatrix; 
    std::vector<std::vector<int>> towerStatsMatrix;
    std::vector<std::vector<sf::Texture>> allTexturesMatrix;
public:
    void imagesReader(std::vector<std::vector<std::string>>& allImagesMatrix);
    void enemyStatsReader(std::vector<std::vector<int>>& enemyStatsMatrix);
    void towerStatsReader(std::vector<std::vector<int>>& towerStatsMatrix);
    bool isNumber(std::string& line);
    void textureMatrixFiller();
};
