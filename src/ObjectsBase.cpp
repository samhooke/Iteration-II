#include <iostream>
#include "ObjectsBase.hpp"
#include "Display.hpp"
#include "LevelManager.hpp"

namespace GameObject {

    // Base
    Base::~Base() {}

    // Static
    Static::Static(int x, int y, GameEngine* game, LevelManager* levelManager) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelManager = levelManager;
    }

    // Dynamic
    Dynamic::Dynamic(int x, int y, GameEngine* game, LevelManager* levelManager) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelManager = levelManager;
    }

    bool Dynamic::SetPos(int x, int y) {
        if (x >= 0 && x < levelManager->levelData->GetWidth() && y >= 0 && y < levelManager->levelData->GetHeight()) {
            if (!useCollisionDetection || (useCollisionDetection && IsPosFree(x, y))) {
                this->x = x;
                this->y = y;
                return true;
            }
        }
        return false;
    }

    bool Dynamic::SetPosRelative(int x, int y) {
        return SetPos(this->x + x, this->y + y);
    }

    bool Dynamic::IsPosFree(int x, int y) {
        return levelManager->levelData->GetTileType(x, y) == TileType::Floor;
    }
}
