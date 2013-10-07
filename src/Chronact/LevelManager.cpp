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
    unsigned int x, y;
    if (f.is_open()) {
        x = y = 0;
        while (getline(f, line)) {
            std::cout << line;

            for (x = 0; x < DISPLAY_WIDTH; x++) {
                if (line[x] == '#')
                    levelData.SetTileType(x, y, TileType::Wall);
                else
                    levelData.SetTileType(x, y, TileType::Floor);
            }
            y++;
        }
        f.close();
    } else {
        std::cout << "Cannot open file: " << levelName << std::endl;
    }

    levelData.CalculateDisplayCharacters();
}

void LevelManager::UpdateDisplay(Display* display) {
    display->SetAll(TILE_BLANK);

    for (unsigned int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (unsigned int x = 0; x < DISPLAY_WIDTH; x++) {
            display->SetDisplayCharacter(x, y, levelData.GetTileDisplayCharacter(x, y));
        }
    }
}
