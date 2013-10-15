#include "Player.hpp"
#include "Tags.hpp"
#include "TimeMachine.hpp"
#include "ObjectsGeneral.hpp"
#include "../LevelData.hpp"
#include "../IterationData.hpp"
#include "../Defs.hpp"
#include "../EventData.hpp"
#include "../Events.hpp"
#include "../General.hpp"
#include "../EndGame.hpp"
#include <iostream>

namespace GameObject {
    Player::Player(int x, int y, GameEngine* game, LevelManager* levelManager, bool original, GameObject::Player* parent, int expiryTime) : Dynamic(x, y, game, levelManager) {
        UpdateDisplayCharacter();
        debugName = "Player";
        TimeDataWrite(true);

        this->original = original;
        this->parent = parent;
        this->expiryTime = expiryTime;
        this->creationTime = levelManager->iterationData->GetTime();
    }

    Player::~Player() {}

    void Player::Update() {
    int time = levelManager->iterationData->GetTime();
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << ::Timestamp(time) << "This is clone '" << cloneDesignation << "' about to update" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
        UpdateDisplayCharacter();

        // index is used by various GetObjectAtPosWithTag() calls
        int index;

        // Only act upon input if we are the player in control, and if the game has not ended
        if (Controlling() && !levelManager->endGame->Ended()) {
            if (game->controls->GetKeyDelaySufficient()) {
                bool moved = false;

                int preMoveX;
                int preMoveY;

                // Only try to move if it is possible to go forward in time!
                if (levelManager->iterationData->CanGoForward()) {
                    bool keyL = game->controls->GetKey(InputKey::Left);
                    bool keyR = game->controls->GetKey(InputKey::Right);
                    bool keyU = game->controls->GetKey(InputKey::Up);
                    bool keyD = game->controls->GetKey(InputKey::Down);

                    int keyMask = (int)keyL | ((int)keyR << 1) | ((int) keyU << 2) | ((int) keyD << 3);

                    preMoveX = x;
                    preMoveY = y;

                    switch (keyMask) {
                        case 0b0001:    moved = SetPosRelative(-1, 0);  break;
                        case 0b0010:    moved = SetPosRelative(+1, 0);  break;
                        case 0b0100:    moved = SetPosRelative(0, -1);  break;
                        case 0b1000:    moved = SetPosRelative(0, +1);  break;
                    }

                    // If we moved on top of a door that is shut, open it and move back
                    index = GetObjectIndexAtPosWithTag(x, y, TAG_DOOR);
                    if (index >= 0) {
                        GameObject::Door* door = (GameObject::Door*)levelManager->levelData->GetObjectPointer(index);
                        if (door->state == false) {
                            // Door is shut, so move back to where we were
                            x = preMoveX;
                            y = preMoveY;

                            // See if we can open the door
                            if (door->requiresKey == false) {
                                // No key is required, so open the door
                                Event::Base* eventDoorOpen = new Event::LinkableStateChange(time, (GameObject::StaticLinkable*)door, this, x, y, door->state);
                                levelManager->eventData->AddEvent(eventDoorOpen);
                            } else {
                                // A key is required, so we cannot open the door
                                // We did not move, nor did we open the door
                                // So set move to false to show nothing happened
                                moved = false;
                            }
                        }
                    }
                }

                // `moved` will never be true if it was not possible to go forward in time
                if (moved) {
                    if (ExpiresNextFrame()) {
                        // It is our expiry time, so do not allow any movement
                        // This is because if we create an Event::PlayerMove, it will cause a paradox
                        // because it will not be able to be fulfilled because in the next timeframe we no longer exist!!
                        x = preMoveX;
                        y = preMoveY;

                        // Now create an expiry event
                        Event::Base* eventPlayerExpire = new Event::PlayerExpire(time, this, x, y);
                        levelManager->eventData->AddEvent(eventPlayerExpire);

                        game->controls->ResetKeyDelay();
                        levelManager->iterationData->GoForward();
                    } else {
                        // It was possible to move to that location, however, we must move only using events
                        // So undo the movent (but remember where we had moved to in xTo,yTo)
                        int xTo = x;
                        int yTo = y;
                        x = preMoveX;
                        y = preMoveY;

                        // Now create an event to do this movement
                        Event::Base* eventPlayerMove = new Event::PlayerMove(time, this, x, y, xTo, yTo);
                        levelManager->eventData->AddEvent(eventPlayerMove);

                        /// PressurePlate (stepping on)
                        // Check for pressure plates in the square we are about to move to
                        index = GetObjectIndexAtPosWithTag(xTo, yTo, TAG_PRESSUREPLATE);
                        if (index >= 0) {
                            // We are going to step on a pressure plate
                            GameObject::PressurePlate* pressurePlate = (GameObject::PressurePlate*)levelManager->levelData->GetObjectPointer(index);

                            // Check if the plate is up
                            if (pressurePlate->state == STATE_PRESSUREPLATE_UP) {
                                // The plate is not pressed, so create an event to press it
                                Event::Base* eventPressurePlatePress = new Event::LinkableStateChange(time, pressurePlate, this, xTo, yTo, STATE_PRESSUREPLATE_UP);
                                levelManager->eventData->AddEvent(eventPressurePlatePress);
                            }
                        }

                        /// PressurePlate (stepping off)
                        // Check for pressure plates in the square we are about to move off
                        index = GetObjectIndexAtPosWithTag(x, y, TAG_PRESSUREPLATE);
                        if (index >= 0) {
                            // We are going to step off a pressure plate
                            GameObject::PressurePlate* pressurePlate = (GameObject::PressurePlate*)levelManager->levelData->GetObjectPointer(index);

                            // Check if the plate is down
                            if (pressurePlate->state == STATE_PRESSUREPLATE_DOWN) {
                                // The plate is pressed, so create an event to release it
                                Event::Base* eventPressurePlateRelease = new Event::LinkableStateChange(time, pressurePlate, this, xTo, yTo, STATE_PRESSUREPLATE_DOWN);
                                levelManager->eventData->AddEvent(eventPressurePlateRelease);
                            }
                        }

                        game->controls->ResetKeyDelay();
                        levelManager->iterationData->GoForward();
                    }
                } else {
                    bool keyAction1 = game->controls->GetKey(InputKey::Action1);
                    bool keyAction2 = game->controls->GetKey(InputKey::Action2);
                    if (keyAction1) {
                        // Perform action with objects we are on
                        int index;

                        //TODO: Make sure only one action can happen at a time
                        // This should not happen so far because all objects are in different tiles
                        // But the current code means that if, say, a time machine and lever were
                        // at the same position, they would both have actions carried out!

                        /// Time Machine
                        index = GetObjectIndexAtPosWithTag(x, y, TAG_TIMEMACHINE);

                        // Check that time is at least 1
                        // This is because a player is not allowed in a time machine when time == 0
                        // This is because a player in a time machine automatically goes back 1 unit in time
                        // This is because of Issue #4 where a player could avoid expiring by going back in time 0 units
                        if (index >= 0 && time >= 1) {
#ifdef DEBUG_TIMETRAVEL
                            std::cout << ::Timestamp(time) << "Clone '" << cloneDesignation << "' has entered a time machine" << std::endl;
#endif // DEBUG_TIMETRAVEL
                            // Pass control to time machine
                            hasControl = false;
                            levelManager->levelData->SetObjectHasControl(index, true);

                            // Tell the time machine information about ourselves so it can pass it on to the clone in the future (past)
                            TimeMachine* timeMachine = (TimeMachine*)levelManager->levelData->GetObjectPointer(index);
                            timeMachine->SetNextCloneDetails(this, time);

                            // Automatically go back in time 1 unit
                            levelManager->iterationData->GoBackward();

                            game->controls->ResetKeyDelay();
                        }

                        /// Lever
                        index = GetObjectIndexAtPosWithTag(x, y, TAG_LEVER);
                        if (index >= 0) {
                            // Get a pointer to the lever
                            Lever* lever = (Lever*)levelManager->levelData->GetObjectPointer(index);

                            // Create a LeverPull event
                            Event::LinkableStateChange* eventLeverPull = new Event::LinkableStateChange(time, (GameObject::StaticLinkable*)lever, this, x, y, lever->state);

                            // Attempt the event forward and backward to verify we satisfy the conditions for it
                            Event::Result resultForward = eventLeverPull->ForwardEvent();
                            Event::Result resultBackward = eventLeverPull->BackwardEvent();

                            if (resultForward.success && resultBackward.success) {
                                // The event was tested successfully, so add it to the events
                                levelManager->eventData->AddEvent(eventLeverPull);
                                game->controls->ResetKeyDelay();
                                levelManager->iterationData->GoForward();
                            } else {
                                std::cout << "ERROR: Could not add Event::LinkableStateChange for the following reasons:" << std::endl;
                                std::cout << "ForwardEvent: " << resultForward.msg << std::endl;
                                std::cout << "BackwardEvent: " << resultBackward.msg << std::endl;
                                delete eventLeverPull;
                            }
                        }

                        /// Terminal
                        index = GetObjectIndexAtPosWithTag(x, y, TAG_TERMINAL);
                        if (index >= 0) {
                            // Check that the meltdown has not occurred yet
                            if (levelManager->iterationData->GetTime() < levelManager->iterationData->GetTimeMeltdown()) {
                                // We win
                                levelManager->endGame->Victory();
                            }
                        }
                    } else if (keyAction2 && levelManager->iterationData->CanGoForward()) {
                        // Move forward in time without moving
                        game->controls->ResetKeyDelay();
                        levelManager->iterationData->GoForward();
                    }
                }
            }
        }
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << ::Timestamp(time) << "This is clone '" << cloneDesignation << "' updated without incident" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
    }

    void Player::UpdateTimeChanged() {
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << ::Timestamp(levelManager->iterationData->GetTime()) << "This is clone '" << cloneDesignation << "' reporting that time has changed" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
        if (Controlling()) {
            if (ExpiresThisFrame()) {
                if (original) {
                    std::cout << "ERROR: Tried to pass control back when we are the original" << std::endl;
                    std::cout << "(my expiryTime is: " << expiryTime << " and my designation is '" << cloneDesignation << "'" << std::endl;
                }
#ifdef DEBUG_TIMETRAVEL
                std::cout << ::Timestamp(levelManager->iterationData->GetTime()) << "Transferring control from clone '" << cloneDesignation << "' to clone '" << parent->cloneDesignation << "'" << std::endl;
#endif // DEBUG_TIMETRAVEL
                // This object has expired, so transfer control back to our parent
                hasControl = false;
                parent->hasControl = true;
                x = -1;
                y = -1;
            }
        }
#ifdef DEBUG_TIMETRAVEL_VERBOSE
        std::cout << ::Timestamp(levelManager->iterationData->GetTime()) << "This is clone '" << cloneDesignation << "' reporting that time changed without incident" << std::endl;
#endif // DEBUG_TIMETRAVEL_VERBOSE
    }

    bool Player::ExpiresThisFrame() {
        return (expiryTime == levelManager->iterationData->GetTime());
    }

    bool Player::ExpiresNextFrame() {
        return (expiryTime - 1 == levelManager->iterationData->GetTime());
    }

    void Player::UpdateDisplayCharacter() {
        if (Controlling())
            displayCharacter = TILE_PLAYER_CONTROLLING;
        else
            displayCharacter = TILE_PLAYER_NOTCONTROLLING;
    }
}
