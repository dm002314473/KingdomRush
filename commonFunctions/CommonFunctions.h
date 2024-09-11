#pragma once

#define LVL1 1
#define LVL2 2
#define LVL3 3
#define CONTINUE 35
#define EXIT 36
#define PAUSE 37
#define FORPAUSE 38
#define REDHEALTHBAR 39
#define GREENHEALTHBAR 40
#define BOLT 4000
#define WAVE_SIGN 5000
#define MAIN_MAP 9999
#define FLAG_FOR_LVL 9998
#define TOWER_STAND 10000
#define TOWER_MENU 10001
#define GIANT 50000
#define GIANT_WALKING1 50001
#define GIANT_WALKING2 50002
#define GIANT_WALKING3 50003
#define HERO_WALKING1 60010
#define HERO_WALKING2 60011
#define HERO_WALKING3 60012
#define TOWER_UPGRADE_SPLIT 69998
#define TOWER_UPGRADE 69999
#define BARRACKS_LVL1 60000
#define BARRACKS_LVL2 60001
#define BARRACKS_LVL3 60002
#define BARRACKS_LVL4_V1 60003
#define BARRACKS_LVL4_V2 60004
#define WIZ_LVL1 70000
#define WIZ_LVL2 70001
#define WIZ_LVL3 70002
#define WIZ_LVL4_V1 70003
#define WIZ_LVL4_V2 70004
#define ARC_LVL1 80000
#define ARC_LVL2 80001
#define ARC_LVL3 80002
#define ARC_LVL4_V1 80003
#define ARC_LVL4_V2 80004
#define BOMBARD_LVL1 90000
#define BOMBARD_LVL2 90001
#define BOMBARD_LVL3 90002
#define BOMBARD_LVL4_V1 90003
#define BOMBARD_LVL4_V2 90004

#include <SFML/Graphics.hpp>
#include <string>

void spriteSetting(sf::Sprite &sprite, sf::Texture &spriteTexture, float scale);
bool isButtonClicked(sf::Sprite &button, sf::Vector2i &mousePos);
void setTextBox(sf::Text& text, sf::Font& font, sf::RectangleShape& box);