#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#define LVL1 1
#define LVL2 2
#define LVL3 3
#define CONTINUE 35
#define EXIT 36
#define PAUSE 37
#define FORPAUSE 38
#define REDHEALTHBAR 39
#define GREENHEALTHBAR 40
#define MAIN_MAP 9999
#define FLAG_FOR_LVL 9998
#define WAVE_SIGN 5000
#define TOWER_STAND 10000
#define TOWER_MENU 10001
#define GIANT 50000
#define GIANT_WALKING1 50001
#define GIANT_WALKING2 50002
#define GIANT_WALKING3 50003
#define HERO_WALKING1 60000
#define HERO_WALKING2 60001
#define HERO_WALKING3 60002
#define WIZ_LVL1 70000
#define ARC_LVL1 80000
#define BOLT 90000

#include <SFML/Graphics.hpp>

void spriteSetting(sf::Sprite &sprite, sf::Texture &spriteTexture, float scale);

#endif