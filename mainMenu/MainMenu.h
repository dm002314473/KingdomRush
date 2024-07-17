#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

class MainMenu
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string mainMenuDocumentPath;
    std::vector<sf::Sprite *> levelFlags;

    std::vector<std::string> levelDocumentPaths;

public:
    MainMenu(std::string mainMenuDocumentPath);
    void handleEvent(sf::Event event);
};