#include <iostream>
#include "ObjectsBase.hpp"
#include "Display.hpp"
#include "LevelData.hpp"

namespace GameObject {

    Base::~Base() {}

    bool Dynamic::SetPos(unsigned int x, unsigned int y) {
        if (x >= 0 && x < levelData->GetWidth() && y >= 0 && y < levelData->GetHeight()) {
            if (!useCollisionDetection || (useCollisionDetection && IsPosFree(x, y))) {
                this->x = x;
                this->y = y;
                return true;
            }
        }
        return false;
    }

    bool Dynamic::SetPosRelative(unsigned int x, unsigned int y) {
        return SetPos(this->x + x, this->y + y);
    }

    bool Dynamic::IsPosFree(unsigned int x, unsigned int y) {
        return levelData->GetTileType(x, y) == TileType::Floor;
    }
}
