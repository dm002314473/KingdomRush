#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MainMenu
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string mainMenuDocumentPath;

    std::vector<std::string> levelDocumentPaths;
};