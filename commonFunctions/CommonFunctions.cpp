#include "CommonFunctions.h"

void spriteSetting(sf::Sprite &sprite, sf::Texture &spriteTexture, float scale)
{
    sprite.setTexture(spriteTexture);
    sprite.setScale(scale, scale);
}

bool isButtonClicked(sf::Sprite &button, sf::Vector2i &mousePos)
{
    if (button.getGlobalBounds().contains((sf::Vector2f)mousePos))
        return true;
    return false;
}