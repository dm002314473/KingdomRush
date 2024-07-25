#include "Level.h"

Level::Level()
{
    // Load data which was read by MainMenu
}

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
    for (auto &enemy : enemies)
        window.draw(enemy->getSprite());
    for (auto &tower : towers)
        window.draw(tower->getSprite());
    for (auto &towerStand : towerStands)
        window.draw(*towerStand);
}