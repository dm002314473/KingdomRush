#include "CommonFunctions.h"


void spriteSetting(sf::Sprite &sprite, sf::Texture &spriteTexture, float scale){
    sprite.setTexture(spriteTexture);
    sprite.setScale(scale, scale);
}