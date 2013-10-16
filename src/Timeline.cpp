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
        char parentDesignation;
        int timeBegin;
        int timeExpire;
        bool controlling;
        bool dead;
    } ;

    // Define as 0 because this value will not be set when the player is in time travel
    // That is because there will be no player controlling (the time machine will be controlling)
    int playerControlling = 0;

    // Read all player information required for the timeline into a vector of PlayerData
    std::vector<PlayerData> players;
    for (int index = 0; index < (int)levelManager->levelData->GetNumObjects(); index++) {
        GameObject::Base* tempObj = levelManager->levelData->GetObjectPointer(index);
        if (tempObj->tag == TAG_PLAYER) {
            PlayerData pd;
            GameObject::Player* player = (GameObject::Player*)tempObj;

            pd.designation = player->cloneDesignation;
            if (player->original) {
                pd.parentDesignation = ' ';
            } else {
                pd.parentDesignation = player->parent->cloneDesignation;
            }
            pd.timeBegin = player->creationTime;
            if (player->original) {
                // Give the original player a really high expiry time because it never expires
                // TODO: When death is added, this may no longer work. In that case, perhaps check
                // for whether the expiry time < 0 to see if it never dies
                pd.timeExpire = 999999;
            } else
                pd.timeExpire = player->expiryTime;
            pd.controlling = player->hasControl;

            if (pd.controlling) {
                // playerControlling stores the position in players of the player for which controlling==true
                // The position in the vector is equal to the size of the vector at the moment
                playerControlling = players.size();
            }
            pd.dead = player->dead;
            players.push_back(pd);
        }
    }

    // Get various time limits
    int timeLimit = levelManager->iterationData->GetTimeLimit();
    int timeMeltdown = levelManager->iterationData->GetTimeMeltdown();
    int currentTime = levelManager->iterationData->GetTime();

    int lineWidth = timeLimit + 6; // Add on six for the "A[" and the "]A |"
    int displayWidth = game->display->GetWidth();
    int displayHeight = game->display->GetHeight();
    int xOffset = (displayWidth - lineWidth) / 2;

    int maxHeight = TIMELINE_HEIGHT_MAX;
    int maxWidth = TIMELINE_WIDTH_MAX;

    if (lineWidth > maxWidth) {
        std::cout << "WARNING: The width of the timeline exceeds the maximum (lineWidth:" << lineWidth << ",maxWidth:" << maxWidth << ")" << std::endl;
    }

    // Place the controlling player in the center
    int iStart = playerControlling - (maxHeight / 2);
    if (iStart < 0) {
        iStart = 0;
    }

    // Show as much as possible
    int iEnd = (int)players.size();
    if (iEnd > maxHeight + iStart)
        iEnd = maxHeight + iStart;

    int iScroll = iStart + ((float)playerControlling / (float)players.size()) * (iEnd - iStart);

    // Loop through PlayerData
    for (int i = iStart; i < iEnd; i++) {

        // Build up a timeline for a player
        std::ostringstream t;
        t << players[i].designation << "[";
        for (int j = 0; j < timeLimit; j++) {
            if (j < players[i].timeBegin) {
                if (j == timeMeltdown) {
                    t << "!";
                } else {
                    t << " ";
                }
            } else if (j < currentTime && j < players[i].timeExpire) {
                if (j == timeMeltdown) {
                    t << "!";
                } else {
                    t << "=";
                }
            } else if (j == currentTime && players[i].controlling) {
                if (players[i].dead) {
                    // If active player is dead, flash between TILE_PLAYER_CONTROLLING and TILE_PLAYER_DEAD
                    // Spends 0.25 seconds on TILE_PLAYER_CONTROLLING and 0.75 seconds on TILE_PLAYER_DEAD
                    if ((int)(game->gameClock->getElapsedTime().asSeconds() / 0.25) % 4 == 0)
                        t << (char)TILE_PLAYER_CONTROLLING;
                    else
                        t << (char)TILE_PLAYER_DEAD;
                } else
                    t << (char)TILE_PLAYER_CONTROLLING;
            } else if (j == currentTime && j < players[i].timeExpire) {
                if (players[i].dead)
                    t << (char)TILE_PLAYER_DEAD;
                else
                    t << (char)TILE_PLAYER_NOTCONTROLLING;
            } else if (j < players[i].timeExpire) {
                if (j == timeMeltdown) {
                    t << "!";
                } else {
                    t << "-";
                }
            } else {
                if (j == timeMeltdown) {
                    t << "!";
                } else {
                    t << " ";
                }
            }
        }
        t << "]" << players[i].parentDesignation << " ";

        if (i == iScroll) {
            t << "*";
        } else {
            t << "|";
        }

        game->display->WriteText(xOffset, displayHeight - maxHeight + i - iStart, t.str().c_str());
    }
}
