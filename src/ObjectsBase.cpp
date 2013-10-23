#include <iostream>
#include "ObjectsBase.hpp"
#include "Display.hpp"
#include "LevelManager.hpp"
#include "IterationData.hpp"
#include "LevelData.hpp"

namespace GameObject {

    /// Base
    Base::~Base() {}

    bool Base::Controlling() {
        if (hasControl) {
            if (canHaveControl) {
                return true;
            } else {
#ifdef DEBUG_VERBOSE
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

    bool Base::IsPosFree(int x, int y, bool checkObjects) {
        //return levelManager->levelData->GetTileType(x, y) == TileType::Floor;
        bool posFree = true;

        if (levelManager->levelData->GetTileType(x, y) != TileType::Floor) {
            posFree = false;
        }

        if (checkObjects) {
            if (posFree) {
                // Check for doors
                int index = GetObjectIndexAtPosWithTag(x, y, TAG_DOOR);

                if (index >= 0) {
                    GameObject::StaticLinkable* door = (GameObject::StaticLinkable*)levelManager->levelData->GetObjectPointer(index);
                    if (door->state == STATE_DOOR_SHUT) {
                        // Door at this position is shut, so the position is not free
                        posFree = false;
                    }
                }
            }
        }

        return posFree;
    }

    // If there is an object at position x,y with tag `tag`, its index is returned
    // If there are multiple objects that match, the first one is returned
    // If there are none that match, -1 is returned
    int Base::GetObjectIndexAtPosWithTag(int x, int y, std::string tag) {
        for (int index = 0; index < levelManager->levelData->GetNumObjects(); index++) {
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

    /// Static
    Static::Static(int x, int y, GameEngine* game, LevelManager* levelManager) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelManager = levelManager;
    }

    /// Dynamic
    Dynamic::Dynamic(int x, int y, GameEngine* game, LevelManager* levelManager) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelManager = levelManager;
    }

    void Dynamic::TimeDataWrite(bool exists) {
        TimeData newTimeData;
        newTimeData.x = x;
        newTimeData.y = y;
        newTimeData.exists = exists;
        timeData[levelManager->iterationData->GetTime()] = newTimeData;
    }

    bool Dynamic::TimeDataAvailable() {
        return (timeData.find(levelManager->iterationData->GetTime()) != timeData.end());
    }

    TimeData Dynamic::TimeDataRead() {
        return timeData[levelManager->iterationData->GetTime()];
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

    /// StaticLinkable
    StaticLinkable::StaticLinkable(int x, int y, GameEngine* game, LevelManager* levelManager, bool state) : Static(x, y, game, levelManager) {
        this->state = state;
    }
}
