#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "LevelManager.hpp"
#include "Tiles.hpp"
#include "Display.hpp"
#include "IterationData.hpp"
#include "LevelData.hpp"
#include "EventData.hpp"

#include "Events.hpp"

LevelManager::LevelManager(GameEngine* game) {
    levelData = new LevelData(game, this);
    iterationData = new IterationData(this);
    eventData = new EventData();
}
LevelManager::~LevelManager() {
    delete levelData;
    delete iterationData;
    delete eventData;
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
#ifdef DEBUG_VERBOSE
                    std::cout << "expectedWidth: " << expectedWidth << std::endl;
#endif
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
#ifdef DEBUG_VERBOSE
                    std::cout << "expectedHeight: " << expectedHeight << std::endl;
#endif
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
                        /// Structure and Mechanisms
                        case '#': // Wall
                            levelData->SetTileDetails(x, y, TileType::Wall, true);
                            break;
                        case 'd': // Door
                            levelData->SetTileDetails(x, y, TileType::Floor, true);
                            levelData->CreateDoor(x, y, false);
                            break;
                        case 'D': // Door (requires key)
                            levelData->SetTileDetails(x, y, TileType::Floor, true);
                            levelData->CreateDoor(x, y, true);
                            break;
                        case 'W': // Window
                            levelData->SetTileDetails(x, y, TileType::Wall, true);
                            levelData->CreateWindow(x, y);
                            break;
                        case 'l': // Lever (state = off)
                            levelData->SetTileDetails(x, y, TileType::Floor, true);
                            levelData->CreateLever(x, y, false);
                            break;
                        case 'L': // Lever (state = on)
                            levelData->SetTileDetails(x, y, TileType::Floor, true);
                            levelData->CreateLever(x, y, true);
                            break;
                        /// Radiation
                        case 'r': // Radiation (weak)
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                            levelData->CreateRadiation(x, y, 0);
                            break;
                        case 'R': // Radiation (strong)
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                            levelData->CreateRadiation(x, y, 1);
                            break;
                        /// Main
                        case 'P': // Player
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                            levelData->CreatePlayerOriginal(x, y); //TODO: Only allow creation of one player (with control)
                            break;
                        case 'T': // Terminal
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                            levelData->CreateTerminal(x, y);
                            break;
                        case 'Y': // Time Machine
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                            levelData->CreateTimeMachine(x, y);
                            break;
                        /// Other
                        case '.': // Floor
                            levelData->SetTileDetails(x, y, TileType::Floor, false);
                        break;
                        case ' ': // Restricted (non-walkable space that should never be accessible)
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

    if (timeChangedForwardFlag && timeChangedBackwardFlag) {
        std::cout << "WARNING: Time changed forward and backward in the same instant" << std::endl;
    }

    // If time has changed backward
    if (timeChangedBackwardFlag) {
        timeChangedBackwardFlag = false;

        // 1) Decrement time
        iterationData->time--;

        // 2) Execute all events for the current time
        eventData->ExecuteBackwardEvents(iterationData->GetTime());

        // Call UpdateTimeChanged() in all GameObjects
        UpdateTimeChanged();
    }

    // Call Update() in all GameObjects
    int num = levelData->GetNumObjects();
    for (int index = 0; index < num; index++) {
        levelData->CallObjectUpdate(index);
    }

    // If time has changed forward
    if (timeChangedForwardFlag) {
        timeChangedForwardFlag = false;

        // 1) Execute all events for the current time
        eventData->ExecuteForwardEvents(iterationData->GetTime());

        // 2) Increment time
        iterationData->time++;

        // Call UpdateTimeChanged() in all GameObjects
        UpdateTimeChanged();
    }
}

void LevelManager::UpdateTimeChanged() {
    // Call UpdateTimeChanged() in all GameObjects
    int num = levelData->GetNumObjects();
    for (int index = 0; index < num; index++) {
        levelData->CallObjectUpdateTimeChanged(index);
    }
}

void LevelManager::UpdateDisplay(GameEngine* game) {

    // Reset all tiles to blank
    game->display->SetAll(TILE_BLANK);

    // Draw the level in the center
    int offsetX = (game->display->GetWidth() - levelData->GetWidth())/2;
    int offsetY = (LEVEL_HEIGHT_MAX - levelData->GetHeight())/2;//(game->display->GetHeight() - levelData->GetHeight())/2;

    // Draw all the walls and floors
    for (int y = 0; y < levelData->GetHeight(); y++) {
        for (int x = 0; x < levelData->GetWidth(); x++) {
            int c = levelData->GetTileDisplayCharacter(x, y);
            game->display->SetDisplayCharacter(x + offsetX, y + offsetY, c);
        }
    }

    // 2D array of int vectors
    //2D//std::vector<int> objectQueue[levelData->GetWidth()][levelData->GetHeight()];
    std::vector<int> objectQueue[levelData->GetWidth() * levelData->GetHeight()];

    // Queue all the objects to be drawn in the 2D array of int vectors
    for (int index = 0; index < levelData->GetNumObjects(); index++) {
        int c = levelData->GetObjectDisplayCharacter(index);
        int x = levelData->GetObjectX(index);
        int y = levelData->GetObjectY(index);

        // Check the object lies within the level boundaries, else objectQueue will not be accessed correctly
        // Objects are sometimes given coordinates outside the boundaries (e.g. -1,-1) in order to make them "invisible"
        if (x >= 0 && x < levelData->GetWidth() && y >= 0 && y < levelData->GetHeight())
            objectQueue[x + y * levelData->GetWidth()].push_back(c);
    }

    // Loop through the 2D array of int vectors
    for (int y = 0; y < levelData->GetHeight(); y++) {
        for (int x = 0; x < levelData->GetWidth(); x++) {
            //2D//int s = objectQueue[x][y].size();
            int s = objectQueue[x + y * levelData->GetWidth()].size();
            // Check whether there is at least one object queued to be drawn at this position
            if (s == 1) {
                //2D//game->display->SetDisplayCharacter(x + offsetX, y + offsetY, (objectQueue[x][y]).at(0));
                game->display->SetDisplayCharacter(x + offsetX, y + offsetY, (objectQueue[x + y * levelData->GetWidth()]).at(0));
            } else if (s > 1) {
                // Choose one of the objects to draw based upon the gameClock

                // Scale the time in order to determine how long each object's display character is shown for
                int t = ((int)(game->gameClock->getElapsedTime().asSeconds() / SECONDS_PER_OBJECT));

                // This is the display character shown between every other tile
                int c = TILE_PLUS;

                // Multiply by 2 because every other character will be TILE_PLUS by default
                //2D//int objectToDraw = t % (objectQueue[x][y].size() * 2);
                int objectToDraw = t % (objectQueue[x + y * levelData->GetWidth()].size() * 2);

                // Set every other tile to the display character of the relevant object
                // Divide by two because objectToDraw was multiplied by two earlier
                if (objectToDraw % 2 == 0)
                    c = (objectQueue[x + y * levelData->GetWidth()]).at(objectToDraw/2);
                    //2D//c = (objectQueue[x][y]).at(objectToDraw/2);

                // Actually update display
                game->display->SetDisplayCharacter(x + offsetX, y + offsetY, c);
            }
        }
    }
}
