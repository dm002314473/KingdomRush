#include "MainMenu.h"

MainMenu::MainMenu(){
    for (int i = 0; i < allImagesMatrix.size(); ++i) {
        allTexturesMatrix[i].resize(allImagesMatrix[i].size());
        for (size_t j = 0; j < allImagesMatrix[i].size(); ++j) {
            if (!allTexturesMatrix[i][j].loadFromFile(allImagesMatrix[i][j])) {
                std::cerr << "Failed to load " << allImagesMatrix[i][j] << std::endl;
            }
        }
    }
}

void MainMenu::imagesReader(std::vector<std::vector<std::string>>& allImagesMatrix){
        std::ifstream file("imagesPaths.txt");
    if (!file.is_open())
    {
        std::cerr << "Unable to open imagesPaths.txt" << std::endl;
        return;
    }
    std::vector<std::string> currentRow;
    std::string line;
    while (std::getline(file, line))
    {
        if (isNumber(line)) {
            if (!currentRow.empty()) {
                allImagesMatrix.push_back(currentRow);
                currentRow.clear();
            }
            currentRow.push_back(line);
        }
        else {
            currentRow.push_back(line);
        }
    }
    if (!currentRow.empty()) {
        allImagesMatrix.push_back(currentRow);
    }

    file.close();
}

bool MainMenu::isNumber(std::string& line) {
    for (char c : line) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void MainMenu::enemyStatsReader(std::vector<std::vector<int>>& enemyStatsMatrix){
    std::ifstream file("enemyStats.txt");
    if (!file.is_open())
    {
        std::cerr << "Unable to open enemyStats.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> currentRow;
        std::string value;
        while (iss >> value) {
            if (isNumber(value)) {
                currentRow.push_back(std::stoi(value));
            }
            else {
                std::cerr << "Invalid number: " << value << std::endl;
                return;
            }
        }
        if (!currentRow.empty()) {
            enemyStatsMatrix.push_back(currentRow);
        }
    }

    file.close();
}


void MainMenu::towerStatsReader(std::vector<std::vector<int>>& towerStatsMatrix) {
    std::ifstream file("tower_stats.txt");
    if (!file.is_open())
    {
        std::cerr << "Unable to open tower_stats.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> currentRow;
        std::string value;
        while (iss >> value) {
            if (isNumber(value)) {
                currentRow.push_back(std::stoi(value));
            }
            else {
                std::cerr << "Invalid number: " << value << std::endl;
                return;
            }
        }
        if (!currentRow.empty()) {
            towerStatsMatrix.push_back(currentRow);
        }
    }

    file.close();
}