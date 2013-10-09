#include "LevelManager.hpp"
#include "Tiles.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

LevelManager::LevelManager(GameEngine* game) {
    levelData = new LevelData(game);
}
LevelManager::~LevelManager() {
    delete levelData;
}

bool LevelManager::StringToInt(std::string &s, int &i) {
    std::istringstream myStream(s);
    return (myStream>>i);
}

void LevelManager::Load(const char* levelName) {
    std::string line;
    std::ifstream f(levelName);
    int x, y, lineNumber;
    int expectedWidth = 80, expectedHeight = 30;
    expectedWidth = 80;
    expectedHeight = 30;

    bool invalidMap = false;
    if (f.is_open()) {
        x = y = lineNumber = 0;
        while (getline(f, line) && !invalidMap && y < expectedHeight) {
            if (lineNumber == 0) {
                // Read expectedWidth
                if (StringToInt(line, expectedWidth)) {
                    std::cout << "expectedWidth: " << expectedWidth << std::endl;
                    if (expectedWidth < LEVEL_WIDTH_MIN || expectedWidth > LEVEL_WIDTH_MAX) {
                        invalidMap = true;
                        std::cout << "ERROR: Level width must fall between " << LEVEL_WIDTH_MIN << " and " << LEVEL_WIDTH_MAX << std::endl;
                    }
                } else {
                    invalidMap = true;
                    std::cout << "ERROR: Expected level width on line " << lineNumber << std::endl;
                }
            } else if (lineNumber == 1) {
                // Read expectedHeight
                if (StringToInt(line, expectedHeight)) {
                    std::cout << "expectedHeight: " << expectedHeight << std::endl;
                    if (expectedHeight < LEVEL_HEIGHT_MIN || expectedHeight > LEVEL_HEIGHT_MAX) {
                        invalidMap = true;
                        std::cout << "ERROR: Level height must fall between " << LEVEL_HEIGHT_MIN << " and " << LEVEL_HEIGHT_MAX << std::endl;
                    }
                } else {
                    invalidMap = true;
                    std::cout << "ERROR: Expected level height on line " << lineNumber << std::endl;
                }

                // Create the blank level
                levelData->CreateBlankLevel(expectedWidth, expectedHeight);
            } else if (lineNumber >= 2 && lineNumber < 2 + expectedHeight) {
                // Read levelData
                if ((int)line.length() == expectedWidth) {
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
                        case 'r':
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                            levelData->CreateRadiation(x, y);
                            break;
                        case 'P':
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                            levelData->CreatePlayer(x, y);
                            break;
                        case '.':
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                        break;
                        case ' ':
                            levelData->SetTileDetails(x, y, TileType::Restricted, false);
                            break;
                        default:
                            invalidMap = true;
                            std::cout << "ERROR: Unknown symbol '" << line[x] << "' at position (" << x << "," << y << ")" << std::endl;
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
            lineNumber++;
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

    int offsetX = 3;
    int offsetY = 2;

    // Draw all the walls and floors
    for (int y = 0; y < levelData->GetHeight(); y++) {
        for (int x = 0; x < levelData->GetWidth(); x++) {
            int c = levelData->GetTileDisplayCharacter(x, y);
            display->SetDisplayCharacter(x + offsetX, y + offsetY, c);
        }
    }

    // Draw all the objects
    for (int index = 0; index < levelData->GetNumObjects(); index++) {
        int c = levelData->GetObjectDisplayCharacter(index);
        int x = levelData->GetObjectX(index);
        int y = levelData->GetObjectY(index);
        display->SetDisplayCharacter(x + offsetX, y + offsetY, c);
    }
}
