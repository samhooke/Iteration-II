#include "Player.hpp"
#include "Tags.hpp"
#include "../IterationData.hpp"
#include "../Defs.hpp"
#include <iostream> // Temporary

namespace GameObject {
    Player::Player(int x, int y, GameEngine* game, LevelManager* levelManager) : Dynamic(x, y, game, levelManager) {
        UpdateDisplayCharacter();

        lastActionTime = game->gameClock->getElapsedTime().asSeconds();

        TimeDataWrite();
    }

    Player::~Player() {}

    void Player::Update() {
        UpdateDisplayCharacter();
        if (Controlling()) {
            bool goForwardOne = false;

            if (game->gameClock->getElapsedTime().asSeconds() > lastActionTime + MOVEMENT_DELAY) {

                bool keyL = game->controls->GetKeyDown(InputKey::Left);
                bool keyR = game->controls->GetKeyDown(InputKey::Right);
                bool keyU = game->controls->GetKeyDown(InputKey::Up);
                bool keyD = game->controls->GetKeyDown(InputKey::Down);

                int keyMask = (int)keyL | ((int)keyR << 1) | ((int) keyU << 2) | ((int) keyD << 3);

                bool moved = false;
                switch (keyMask) {
                    case 0b0001:    moved = SetPosRelative(-1, 0);  break;
                    case 0b0010:    moved = SetPosRelative(+1, 0);  break;
                    case 0b0100:    moved = SetPosRelative(0, -1);  break;
                    case 0b1000:    moved = SetPosRelative(0, +1);  break;
                }

                if (moved)
                    goForwardOne = true;

                // Only perform an action if a movement has not occured, to avoid two events happening in one frame
                if (!moved) {
                    bool keyAction1 = game->controls->GetKeyDown(InputKey::Action1);
                    bool keyAction2 = game->controls->GetKeyDown(InputKey::Action2);
                    if (keyAction1) {
                        // Perform action with objects we are on
                        int index = GetObjectIndexAtPosWithTag(x, y, TAG_TIMEMACHINE);
                        if (index >= 0) {
                            // Pass control to time machine
                            hasControl = false;
                            levelManager->levelData->SetObjectHasControl(index, true);
                        }
                    } else if (keyAction2) {
                        // Move forward in time without moving
                        goForwardOne = true;
                    }
                }
            }

            if (goForwardOne) {
                lastActionTime = game->gameClock->getElapsedTime().asSeconds();
                levelManager->iterationData->Forward();
                TimeDataWrite();
            }
        }
    }

    void Player::UpdateTimeChanged() {
        if (!Controlling()) {
            TimeData currentTimeData = TimeDataRead();
            x = currentTimeData.x;
            y = currentTimeData.y;
        }
    }

    void Player::UpdateDisplayCharacter() {
        if (Controlling())
            displayCharacter = TILE_PLAYER_CONTROLLING;
        else
            displayCharacter = TILE_PLAYER_NOTCONTROLLING;
    }
}
