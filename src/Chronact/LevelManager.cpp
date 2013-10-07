#include "LevelManager.hpp"
#include "Tiles.hpp"
#include <iostream>
#include <string>
#include <fstream>

LevelManager::LevelManager() {}
LevelManager::~LevelManager() {}

void LevelManager::Load(const char* levelName) {
    std::cout << "Load...";
    std::string line;
    //std::ifstream f(levelName);
    std::cout << "ifstream";
    std::ifstream f;
    std::cout << "f.open()";
    f.open(levelName);
    std::cout << "!?!...";
    unsigned int x, y;
    unsigned int expectedWidth, expectedHeight;
    std::cout << "Asdf...";
    expectedWidth = DISPLAY_WIDTH;
    expectedHeight = DISPLAY_HEIGHT;

    levelData = new LevelData();
    std::cout << "Opening file...";
    bool invalidMap = false;
    if (f.is_open()) {
        x = y = 0;
        while (getline(f, line) && !invalidMap && y < expectedHeight) {
            if (line.length() == expectedWidth) {
                for (x = 0; x < expectedWidth; x++) {
                    // Convert the read symbol into a TileType
                    if (line[x] == '#')
                        levelData->SetTileType(x, y, TileType::Wall);
                    else
                        levelData->SetTileType(x, y, TileType::Floor);
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
                levelData->SetTileType(x, y, TileType::Wall);
            }
        }
    } else {
        // Map was valid, so work out what characters should be displayed
        levelData->CalculateDisplayCharacters();
    }
}

void LevelManager::UpdateDisplay(Display* display) {
    std::cout << "display->SetAll()" << std::endl;
    display->SetAll(TILE_BLANK);
    std::cout << "Going into loop" << std::endl;
    for (unsigned int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (unsigned int x = 0; x < DISPLAY_WIDTH; x++) {
            //std::cout << "Setting characters" << std::endl;
            //display->SetDisplayCharacter(x, y, 1);
            int c = levelData->GetTileDisplayCharacter(x, y);
            // std::cout << "got character" << std::endl;
            display->SetDisplayCharacter(x, y, c);
            //std::cout << "They are set" << std::endl;
        }
    }
}
