#include "Level.h"

// Should try to remove the texture variable from class and use texture directly from AllTextureMatrix
Level::Level(int levelIndex, MainMenu &mainMenu)
{
    backgroundTexture = mainMenu.getTexture(mainMenu.getAllTexturesMatrix(), levelIndex, 0);

    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        levelBackground.setTexture(backgroundTexture);
        std::cout << "ucitan sprite" << std::endl;
    }
    else
        std::cerr << "Failed to get valid texture." << std::endl;
}

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Event &event, Game &game)
{
    // Handle creating towers, and starting new waves
    /*
    if (towerStandClicked)
        handleTowerStandClick()
    else if (startWaveButtonClicked)
        handleStartWaveButtonClick()
    */
}

void Level::update()
{
    // Implement logic for enemy movement and tower shooting
}

void Level::render(sf::RenderWindow &window)
{
    window.draw(levelBackground);
    for (auto &enemy : enemies)
        window.draw(enemy->getSprite());
    for (auto &tower : towers)
        window.draw(tower->getSprite());
    for (auto &towerStand : towerStands)
        window.draw(*towerStand);
}