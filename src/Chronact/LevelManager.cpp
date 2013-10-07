#include "LevelManager.hpp"
#include "Tiles.hpp"
#include <iostream>
#include <string>
#include <fstream>

LevelManager::LevelManager() {}
LevelManager::~LevelManager() {}

void LevelManager::Load(const char* levelName) {
    std::string line;
    std::ifstream f(levelName);
    if (f.is_open()) {
        while (getline(f, line)) {
            std::cout << line;// << std::endl;
        }
        f.close();
    } else {
        std::cout << "Cannot open file: " << levelName << std::endl;
    }
}

void LevelManager::UpdateDisplay(Display* display) {
    display->SetAll(TILE_BLANK);
}
