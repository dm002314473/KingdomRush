#include "CommonFunctions.h"

void spriteSetting(sf::Sprite &sprite, sf::Texture &spriteTexture, float scale)
{
    sprite.setTexture(spriteTexture);
    sprite.setScale(scale, scale);
}

bool isButtonClicked(sf::Sprite &button, sf::Vector2i &mousePos)
{
    if (button.getGlobalBounds().contains((sf::Vector2f)mousePos))
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
    return false;
}

void setTextBox(sf::Text& text, sf::Font& font, sf::RectangleShape& box){
    box.setPosition(10, 10);
    box.setSize(sf::Vector2f(100, 30));

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(15, 15);
}