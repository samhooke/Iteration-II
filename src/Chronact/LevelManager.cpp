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
    unsigned int expectedWidth, expectedHeight;
    expectedWidth = DISPLAY_WIDTH;
    expectedHeight = DISPLAY_HEIGHT;

    levelData = new LevelData();
    bool invalidMap = false;
    if (f.is_open()) {
        x = y = 0;
        while (getline(f, line) && !invalidMap && y < expectedHeight) {
            if (line.length() == expectedWidth) {
                for (x = 0; x < expectedWidth; x++) {
                    // Convert the read symbol into a TileType
                    if (line[x] == '#')
                        levelData->SetTileDetails(x, y, TileType::Wall);
                    else if (line[x] == 'D')
                        levelData->SetTileDetails(x, y, TileType::Door);
                    else
                        levelData->SetTileDetails(x, y, TileType::Floor);
                }
            } else {
                invalidMap = true;
                std::cout << "ERROR: Invalid map. Incorrect width on row " << y << std::endl;
                std::cout << "(Should have been width " << expectedWidth << ". Actual width was " << line.length() << ")" << std::endl;
            }
            y++;
        }
        f.close();

        if (y != expectedHeight) {
            invalidMap = true;
            std::cout << "ERROR: Invalid map. Incorrect number of rows" << std::endl;
            std::cout << "(Should have had " << expectedHeight << " rows)" << std::endl;
        }

    } else {
        invalidMap = true;
        std::cout << "ERROR: Cannot open file: " << levelName << std::endl;
    }
    if (invalidMap) {
        // Map was invalid, so just populated the levelData with walls
        for (y = 0; y < expectedHeight; y++) {
            for (x = 0; x < expectedWidth; x++) {
                levelData->SetTileDetails(x, y, TileType::Wall);
            }
        }
    } else {
        // Map was valid, so work out what characters should be displayed
        levelData->CalculateDisplayCharacters();
    }
}

void LevelManager::UpdateDisplay(Display* display) {
    display->SetAll(TILE_BLANK);
    for (unsigned int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (unsigned int x = 0; x < DISPLAY_WIDTH; x++) {
            int c = levelData->GetTileDisplayCharacter(x, y);
            display->SetDisplayCharacter(x, y, c);
        }
    }
}
