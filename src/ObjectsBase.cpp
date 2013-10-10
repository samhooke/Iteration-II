#include <iostream>
#include "ObjectsBase.hpp"
#include "Display.hpp"
#include "LevelManager.hpp"
#include "IterationData.hpp"

namespace GameObject {

    // Base
    Base::~Base() {}

    bool Base::Controlling() {
        if (hasControl) {
            if (canHaveControl) {
                return true;
            } else {
#if DEBUG_VERBOSE
                // This would print out once per frame, which is a lot
                std::cout << "ERROR: An object has control which cannot assume control" << std::endl;
#endif
            }
        }
        return false;
    }

    void Base::UpdateTimeChanged() {
        //std::cout << "Time changed!" << std::endl;
    }

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

    void Dynamic::TimeDataWrite() {
        TimeData newTimeData;
        newTimeData.x = x;
        newTimeData.y = y;
        timeData[levelManager->iterationData->GetCurrentIteration()] = newTimeData;
    }

    TimeData Dynamic::TimeDataRead() {
        return timeData[levelManager->iterationData->GetCurrentIteration()];
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

    // If there is an object at position x,y with tag `tag`, its index is returned
    // If there are multiple objects that match, the first one is returned
    // If there are none that match, -1 is returned
    int Dynamic::GetObjectIndexAtPosWithTag(int x, int y, std::string tag) {
        for (unsigned int index = 0; index < levelManager->levelData->GetNumObjects(); index++) {
            int objX = levelManager->levelData->GetObjectX(index);
            int objY = levelManager->levelData->GetObjectY(index);

            if (objX == x && objY == y) {
                if (levelManager->levelData->CompareObjectTag(index, tag)) {
                    return index;
                }
            }
        }
    return -1;
    }
}
