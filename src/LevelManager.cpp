#include "LevelManager.hpp"
#include "Tiles.hpp"
#include <iostream>
#include <string>
#include <fstream>

LevelManager::LevelManager(GameEngine* game) {
    levelData = new LevelData(game);
}
LevelManager::~LevelManager() {
    delete levelData;
}

void LevelManager::Load(const char* levelName) {
    std::string line;
    std::ifstream f(levelName);
    unsigned int x, y;
    unsigned int expectedWidth, expectedHeight;
    expectedWidth = DISPLAY_WIDTH;
    expectedHeight = DISPLAY_HEIGHT;

    bool invalidMap = false;
    if (f.is_open()) {
        x = y = 0;
        while (getline(f, line) && !invalidMap && y < expectedHeight) {
            if (line.length() == expectedWidth) {
                for (x = 0; x < expectedWidth; x++) {
                    // Convert the read symbol into a TileType
                    switch (line[x]) {
                    case '#':
                        levelData->SetTileDetails(x, y, TileType::Wall, true);
                        break;
                    case 'D':
                        levelData->SetTileDetails(x, y, TileType::Floor, true);
                        levelData->CreateDoor(x, y);
                        break;
                    case 'P':
                        levelData->SetTileDetails(x, y, TileType::Floor, false);
                        levelData->CreatePlayer(x, y);
                        break;
                    case ' ':
                    default:
                        levelData->SetTileDetails(x, y, TileType::Floor, false);
                        break;
                    }
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
                levelData->SetTileDetails(x, y, TileType::Wall, true);
            }
        }
    } else {
        // Map was valid, so work out what characters should be displayed
        levelData->CalculateDisplayCharacters();
    }
}

void LevelManager::Update(GameEngine* game) {
    // Call Update() in all GameObjects
    for (int index = 0; index < levelData->GetNumObjects(); index++) {
        levelData->CallObjectUpdate(index);
    }
}

void LevelManager::UpdateDisplay(Display* display) {

    // Reset all tiles to blank
    display->SetAll(TILE_BLANK);

    // Draw all the walls and floors
    for (unsigned int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (unsigned int x = 0; x < DISPLAY_WIDTH; x++) {
            int c = levelData->GetTileDisplayCharacter(x, y);
            display->SetDisplayCharacter(x, y, c);
        }
    }

    // Draw all the objects
    for (int index = 0; index < levelData->GetNumObjects(); index++) {
        int c = levelData->GetObjectDisplayCharacter(index);
        unsigned int x = levelData->GetObjectX(index);
        unsigned int y = levelData->GetObjectY(index);
        display->SetDisplayCharacter(x, y, c);
    }
}
