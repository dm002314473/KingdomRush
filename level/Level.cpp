#include "Level.h"

// Should try to remove the texture variable from class and use texture directly from AllTextureMatrix
Level::Level(int levelIndex, MainMenu &MainMenu) : mainMenu(MainMenu)
{
    backgroundTexture = mainMenu.getTexture(mainMenu.getAllTexturesMatrix(), levelIndex, 0);

    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        levelBackground.setTexture(backgroundTexture);
        std::cout << "ucitan sprite" << std::endl;
    }
    else
        std::cerr << "Failed to get valid texture." << std::endl;

    newWaveButtonTexture.loadFromFile("GeneralRehearsal/images/wiz_lvl1.png");
    newWaveButton.setTexture(newWaveButtonTexture);
    newWaveButton.setPosition(20, 20);
}

sf::Sprite Level::getSprite() { return levelBackground; }

void Level::handleEvent(sf::Vector2i &mousePos, Game &game)
{
    // Handle creating towers, and starting new waves
    if (newWaveButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
    {
        // Instead of creating one enemy, here the wave should be started
        Enemy *enemy = new Enemy(mainMenu);
        enemies.push_back(enemy);

        // newWave
        startNewWave(1);
    }
}

void Level::update()
{
    for (auto &enemy : enemies)
        enemy->move();
    // Implement logic for tower shooting
}

void Level::render(sf::RenderWindow &window)
{
    window.draw(levelBackground);
    window.draw(newWaveButton);
    for (auto &enemy : enemies)
        window.draw(enemy->getSprite());
    for (auto &tower : towers)
        window.draw(tower->getSprite());
    for (auto &towerStand : towerStands)
        window.draw(*towerStand);
}

void Level::startNewWave(int waveIndex)
{
}