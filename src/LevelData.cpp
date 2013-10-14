#include <iostream>
#include "LevelData.hpp"
#include "Tiles.hpp"
#include "General.hpp"

#include "objects/Tags.hpp"
#include "objects/Player.hpp"
#include "objects/TimeMachine.hpp"
#include "objects/ObjectsGeneral.hpp"
#include "objects/Radiation.hpp"
#include "IterationData.hpp"

LevelData::LevelData(GameEngine* game, LevelManager* levelManager) {
    // Requires a reference to GameEngine & LevelManager which it passes on to created objects
    this->game = game;
    this->levelManager = levelManager;
}

LevelData::~LevelData() {
    // Destroy all generated GameObjects
    for (int i = 0; i < (int)levelObjects.size(); i++) {
        delete levelObjects[i];
    }
}

void LevelData::CreateBlankLevel(int width, int height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < width * height; i++) {
        levelTiles.push_back(LevelTile(TileType::Floor));
    }
}

void LevelData::SetTileDetails(int x, int y, TileType type, bool connectsWithWall) {
    int index = x + y * width;
    levelTiles[index].type = type;
    levelTiles[index].connectsWithWall = connectsWithWall;
}

int LevelData::GetTileDisplayCharacter(int x, int y) {
    int index = x + y * width;
    return levelTiles[index].displayCharacter;
}

TileType LevelData::GetTileType(int x, int y) {
    int index = x + y * width;
    return levelTiles[index].type;
}

void LevelData::CalculateDisplayCharacters() {
    bool wall_n, wall_e, wall_s, wall_w;
    int index_n, index_e, index_s, index_w;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = x + y * width;

            index_n = x + (y - 1) * width;
            index_e = (x + 1) + y * width;
            index_s = x + (y + 1) * width;
            index_w = (x - 1) + y * width;

            wall_n = wall_e = wall_s = wall_w = false;

            if (y >= 1)         {wall_n = (levelTiles[index_n].connectsWithWall);} else {wall_n = false;}
            if (x < width - 1)  {wall_e = (levelTiles[index_e].connectsWithWall);} else {wall_e = false;}
            if (y < height - 1) {wall_s = (levelTiles[index_s].connectsWithWall);} else {wall_s = false;}
            if (x >= 1)         {wall_w = (levelTiles[index_w].connectsWithWall);} else {wall_w = false;}

            int c = TILE_QUESTION; // Default is question mark

            if (levelTiles[index].type == TileType::Wall) {

                int wallMask = ((int)wall_n) | ((int)wall_e << 1) | ((int)wall_s << 2) | ((int)wall_w << 3);

                switch (wallMask) {
                case 0b0000:    c = TILE_WD_PILLAR; break;
                case 0b0001:    c = TILE_WD_N;      break;
                case 0b0010:    c = TILE_WD_E;      break;
                case 0b0011:    c = TILE_WD_NE;     break;
                case 0b0100:    c = TILE_WD_S;      break;
                case 0b0101:    c = TILE_WD_NS;     break;
                case 0b0110:    c = TILE_WD_ES;     break;
                case 0b0111:    c = TILE_WD_NES;    break;
                case 0b1000:    c = TILE_WD_W;      break;
                case 0b1001:    c = TILE_WD_NW;     break;
                case 0b1010:    c = TILE_WD_EW;     break;
                case 0b1011:    c = TILE_WD_NEW;    break;
                case 0b1100:    c = TILE_WD_SW;     break;
                case 0b1101:    c = TILE_WD_NSW;    break;
                case 0b1110:    c = TILE_WD_ESW;    break;
                case 0b1111:    c = TILE_WD_NESW;   break;
                default:        c = TILE_QUESTION;  break; // Error
                }
            } else if (levelTiles[index].type == TileType::Floor) {
                if (index % 17 == 0 || index % 23 == 0 || index % 7 == 0 || index % 13 == 0)
                    c = TILE_COMMA;
                else if (index % 19 == 0 || index % 29 == 0 || index % 11 == 0 || index % 31 == 0)
                    c = TILE_GRAVEACCENT;
                else
                    c = TILE_FULLSTOP;
            } else if (levelTiles[index].type == TileType::Restricted) {
                c = TILE_BLANK;
            }

            levelTiles[index].displayCharacter = c;
        }
    }
}

int LevelData::GetWidth() {
    return width;
}

int LevelData::GetHeight() {
    return height;
}

int LevelData::GetNumObjects() {
    return (int)levelObjects.size();
}

int LevelData::GetObjectDisplayCharacter(int index) {
    return levelObjects[index]->displayCharacter;
}

int LevelData::GetObjectX(int index) {
    return levelObjects[index]->x;
}

int LevelData::GetObjectY(int index) {
    return levelObjects[index]->y;
}

GameObject::Base* LevelData::GetObjectPointer(int index) {
    return levelObjects[index];
}

void LevelData::SetObjectHasControl(int index, bool hasControl) {
    if (levelObjects[index]->canHaveControl)
        levelObjects[index]->hasControl = hasControl;
    else {
        std::cout << "ERROR: Tried to pass control to an object that cannot assume control" << std::endl;
    }
}

bool LevelData::CompareObjectTag(int index, std::string tag) {
    return levelObjects[index]->tag == tag;
}

void LevelData::CallObjectUpdate(int index) {
#ifdef DEBUG_TIMETRAVEL_VERBOSE
    std::cout << ::Timestamp(levelManager->iterationData->GetTime()) << "About to call Update() on an object" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
    levelObjects[index]->Update();
#ifdef DEBUG_TIMETRAVEL_VERBOSE
    std::cout << ::Timestamp(levelManager->iterationData->GetTime()) << "Called Update() successfully" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
}

void LevelData::CallObjectUpdateTimeChanged(int index) {
    levelObjects[index]->UpdateTimeChanged();
}

void LevelData::CreatePlayerOriginal(int x, int y) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreatePlayerOriginal(" << x << "," << y << ")" << std::endl;
#endif
    GameObject::Base* obj = new GameObject::Player(x, y, game, levelManager, true, NULL, -1);
    obj->tag = TAG_PLAYER;
    obj->canHaveControl = true;
    obj->hasControl = true;
#ifdef DEBUG_TIMETRAVEL
    std::cout << ::Timestamp(levelManager->iterationData->GetTime()) << "Created player (original) with designation '" << nextCloneDesignation << "'" << std::endl;
#endif
    ((GameObject::Player*)obj)->cloneDesignation = nextCloneDesignation;
    nextCloneDesignation++;
    levelObjects.push_back(obj);
}

void LevelData::CreatePlayer(int x, int y, bool hasControl, GameObject::Player* parent, int expiryTime) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreatePlayer(" << x << "," << y << ")" << std::endl;
#endif
    GameObject::Base* obj = new GameObject::Player(x, y, game, levelManager, false, parent, expiryTime);
    obj->tag = TAG_PLAYER;
    obj->canHaveControl = true;
    obj->hasControl = hasControl;
#ifdef DEBUG_TIMETRAVEL
    std::cout << ::Timestamp(levelManager->iterationData->GetTime()) << "Created player with designation '" << nextCloneDesignation << "', whose parent is '" << parent->cloneDesignation << "'" << std::endl;
#endif
    ((GameObject::Player*)obj)->cloneDesignation = nextCloneDesignation;
    nextCloneDesignation++;
    levelObjects.push_back(obj);
}

void LevelData::CreateDoor(int x, int y, bool requiresKey) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreateDoor(" << x << "," << y << ")" << std::endl;
#endif
    GameObject::Base* obj = new GameObject::Door(x, y, game, levelManager, requiresKey);
    obj->tag = TAG_DOOR;
    levelObjects.push_back(obj);
}

void LevelData::CreateLever(int x, int y, bool state) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreateLever(" << x << "," << y << ")" << std::endl;
#endif
    GameObject::Base* obj = new GameObject::Lever(x, y, game, levelManager, state);
    obj->tag = TAG_LEVER;
    levelObjects.push_back(obj);
}

void LevelData::CreateWindow(int x, int y) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreateWindow(" << x << "," << y << ")" << std::endl;
#endif
    levelObjects.push_back(new GameObject::Window(x, y, game, levelManager));
}

void LevelData::CreateTerminal(int x, int y) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreateTerminal(" << x << "," << y << ")" << std::endl;
#endif
    levelObjects.push_back(new GameObject::Terminal(x, y, game, levelManager));
}

void LevelData::CreateTimeMachine(int x, int y) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreateTimeMachine(" << x << "," << y << ")" << std::endl;
#endif
    GameObject::Base* obj = new GameObject::TimeMachine(x, y, game, levelManager);
    obj->tag = TAG_TIMEMACHINE;
    obj->canHaveControl = true;
    levelObjects.push_back(obj);
}

void LevelData::CreateRadiation(int x, int y, int intensity) {
#ifdef DEBUG_VERBOSE
    std::cout << "CreateRadiation(" << x << "," << y << ")" << std::endl;
#endif
    if (intensity == 0)
        levelObjects.push_back(new GameObject::RadiationWeak(x, y, game, levelManager));
    else if (intensity == 1)
        levelObjects.push_back(new GameObject::RadiationStrong(x, y, game, levelManager));
    else
        std::cout << "WARNING: Tried to create radiation with an invalid intensity" << std::endl;
}
