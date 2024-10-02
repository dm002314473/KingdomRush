#include "Wave.h"

Wave::Wave() {}

void Wave::pushEnemyToWave(int nameCode, int spawnTime) { wave.push_back(std::make_pair(nameCode, spawnTime)); }

int Wave::getSize() { return wave.size(); }
std::pair<int, int> Wave::getEnemy(int index) { return wave[index]; }

void Wave::erase() { wave.clear(); }