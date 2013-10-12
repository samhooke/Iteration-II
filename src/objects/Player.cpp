#include "Player.hpp"
#include "Tags.hpp"
#include "TimeMachine.hpp"
#include "../LevelData.hpp"
#include "../IterationData.hpp"
#include "../Defs.hpp"
#include <iostream> // Temporary

namespace GameObject {
    Player::Player(int x, int y, GameEngine* game, LevelManager* levelManager, bool original, GameObject::Player* parent, int expiryTime) : Dynamic(x, y, game, levelManager) {
        UpdateDisplayCharacter();
        debugName = "Player";
        TimeDataWrite(true);

        this->original = original;
        this->parent = parent;
        this->expiryTime = expiryTime;
    }

    Player::~Player() {}

    void Player::Update() {
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << Timestamp() << "This is clone '" << cloneDesignation << "' about to update" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
        UpdateDisplayCharacter();
        if (Controlling()) {
            if (game->controls->GetKeyDelaySufficient()) {
                bool moved = false;

                // Only try to move if it is possible to go forward in time!
                if (levelManager->iterationData->CanGoForward()) {
                    bool keyL = game->controls->GetKey(InputKey::Left);
                    bool keyR = game->controls->GetKey(InputKey::Right);
                    bool keyU = game->controls->GetKey(InputKey::Up);
                    bool keyD = game->controls->GetKey(InputKey::Down);

                    int keyMask = (int)keyL | ((int)keyR << 1) | ((int) keyU << 2) | ((int) keyD << 3);


                    switch (keyMask) {
                        case 0b0001:    moved = SetPosRelative(-1, 0);  break;
                        case 0b0010:    moved = SetPosRelative(+1, 0);  break;
                        case 0b0100:    moved = SetPosRelative(0, -1);  break;
                        case 0b1000:    moved = SetPosRelative(0, +1);  break;
                    }
                }

                // `moved` will never be true if it was not possible to go forward in time
                if (moved) {
                    // Moved, so go forward in time and save our position
                    game->controls->ResetKeyDelay();
                    levelManager->iterationData->GoForward();
                    TimeDataWrite(true);
                } else {
                    bool keyAction1 = game->controls->GetKey(InputKey::Action1);
                    bool keyAction2 = game->controls->GetKey(InputKey::Action2);
                    if (keyAction1) {
                        // Perform action with objects we are on
                        int index = GetObjectIndexAtPosWithTag(x, y, TAG_TIMEMACHINE);
                        if (index >= 0) {
#ifdef DEBUG_TIMETRAVEL
                            std::cout << Timestamp() << "Clone '" << cloneDesignation << "' has entered a time machine" << std::endl;
#endif // DEBUG_TIMETRAVEL
                            // Pass control to time machine
                            hasControl = false;
                            levelManager->levelData->SetObjectHasControl(index, true);

                            // Tell the time machine information about ourselves so it can pass it on to the clone in the future (past)
                            TimeMachine* timeMachine = (TimeMachine*)levelManager->levelData->GetObjectPointer(index);
                            timeMachine->SetNextCloneDetails(this, levelManager->iterationData->GetTime());

                            game->controls->ResetKeyDelay();
                        }
                    } else if (keyAction2 && levelManager->iterationData->CanGoForward()) {
                        // Move forward in time without moving
                        game->controls->ResetKeyDelay();
                        levelManager->iterationData->GoForward();
                        TimeDataWrite(true);
                    }
                }
            }
        }
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << Timestamp() << "This is clone '" << cloneDesignation << "' updated without incident" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
    }

    void Player::UpdateTimeChanged() {
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << Timestamp() << "This is clone '" << cloneDesignation << "' reporting that time has changed" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
        if (Controlling()) {
            if (expiryTime == levelManager->iterationData->GetTime()) {
                if (original) {
                    std::cout << "ERROR: Tried to pass control back when we are the original" << std::endl;
                    std::cout << "(my expiryTime is: " << expiryTime << " and my designation is '" << cloneDesignation << "'" << std::endl;
                }
#ifdef DEBUG_TIMETRAVEL
                std::cout << Timestamp() << "Transferring control from clone '" << cloneDesignation << "' to clone '" << parent->cloneDesignation << "'" << std::endl;
#endif // DEBUG_TIMETRAVEL
                // This object has expired, so transfer control back to our parent
                hasControl = false;
                parent->hasControl = true;
                x = -1;
                y = -1;
                TimeDataWrite(false); // 'false' because we do not exist in this time
            }
        }

        if (!Controlling()) {
            bool exists = false;

            // Time data being available does not mean the object necessarily exists at this point in time
            // So first check if data is available, and if true, also check whether the data says we exist!
            if (TimeDataAvailable()) {
                TimeData currentTimeData = TimeDataRead();
                if (currentTimeData.exists) {
                    exists = true;
                    x = currentTimeData.x;
                    y = currentTimeData.y;
                }
            }
            if (!exists) {
                // If we do not exist, simply move ourselves out of the display so we are not rendered
                x = -1;
                y = -1;
            }
        }
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << Timestamp() << "This is clone '" << cloneDesignation << "' reporting that time changed without incident" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
    }

    void Player::UpdateDisplayCharacter() {
        if (Controlling())
            displayCharacter = TILE_PLAYER_CONTROLLING;
        else
            displayCharacter = TILE_PLAYER_NOTCONTROLLING;
    }
}
