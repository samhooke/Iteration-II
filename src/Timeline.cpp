#include <iostream>
#include <sstream>
#include "Timeline.hpp"
#include "Display.hpp"
#include "Tiles.hpp"

#include "objects/Player.hpp"
#include "LevelData.hpp"
#include "IterationData.hpp"


Timeline::Timeline() {}

Timeline::~Timeline() {}

void Timeline::UpdateDisplay(GameEngine* game, LevelManager* levelManager) {

    struct PlayerData {
        char designation;
        int timeBegin;
        int timeExpire;
        bool controlling;
    } ;

    std::vector<PlayerData> players;
    for (int index = 0; index < (int)levelManager->levelData->GetNumObjects(); index++) {
        GameObject::Base* tempObj = levelManager->levelData->GetObjectPointer(index);
        if (tempObj->tag == TAG_PLAYER) {
            PlayerData pd;
            GameObject::Player* player = (GameObject::Player*)tempObj;

            pd.designation = player->cloneDesignation;
            pd.timeBegin = player->creationTime;
            if (player->original)
                pd.timeExpire = 999999;
            else
                pd.timeExpire = player->expiryTime;
            pd.controlling = player->hasControl;
            players.push_back(pd);
        }
    }

    int timeLimit = levelManager->iterationData->GetTimeLimit();
    int currentTime = levelManager->iterationData->GetTime();

    for (int i = 0; i < (int)players.size(); i++) {
        std::ostringstream t;
        t << "[" << players[i].designation << ":";
        for (int j = 0; j < timeLimit; j++) {
            if (j < players[i].timeBegin) {
                t << " ";
            } else if (j < currentTime && j < players[i].timeExpire) {
                t << "=";
            } else if (j == currentTime && players[i].controlling) {
                t << "@";
            } else if (j < players[i].timeExpire) {
                t << "-";
            } else {
                t << " ";
            }
        }
        t << "]";
        game->display->WriteText(0, 30 + i, t.str().c_str());
    }
}
