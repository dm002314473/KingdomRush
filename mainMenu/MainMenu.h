#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

class MainMenu
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string mainMenuDocumentPath;

    void levelReader(int index);
};