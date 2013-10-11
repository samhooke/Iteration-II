#include "TimeMachine.hpp"
#include "../Tiles.hpp"
#include "../IterationData.hpp"
#include "../Defs.hpp"

namespace GameObject {
    TimeMachine::TimeMachine(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        UpdateDisplayCharacter();

        lastActionTime = game->gameClock->getElapsedTime().asSeconds();
    }

    TimeMachine::~TimeMachine() {}

    void TimeMachine::Update() {
        UpdateDisplayCharacter();
        if (Controlling()) {
            if (game->gameClock->getElapsedTime().asSeconds() > lastActionTime + MOVEMENT_DELAY) {
                bool keyAction1 = game->controls->GetKeyDown(InputKey::Action1);
                bool keyAction2 = game->controls->GetKeyDown(InputKey::Action2);
                if (keyAction1) {
                    // IMPORTANT: This always runs immediately when the player gets into the time machine
                    // This is because the GetKeyDown(InputKey::Action1) function, which triggers this event
                    // is true for both the Player and for the TimeMachine

                    // Go back in time
                    lastActionTime = game->gameClock->getElapsedTime().asSeconds();
                    levelManager->iterationData->Backward();
                } else if (keyAction2) {
                    // Exit time machine (create new player and pass control to them)
                    levelManager->levelData->CreatePlayer(x, y, true);
                    hasControl = false;
                }
            }
        }
    }

    void TimeMachine::UpdateDisplayCharacter() {
        if (Controlling()) {
            int t = ((int)(game->gameClock->getElapsedTime().asSeconds() / TIMEMACHINE_SECONDS_PER_DISPLAYCHARACTER));
            if (t % 2 == 0)
                displayCharacter = TILE_TIMEMACHINE_ACTIVE_1;
            else
                displayCharacter = TILE_TIMEMACHINE_ACTIVE_2;
        } else {
            displayCharacter = TILE_TIMEMACHINE;
        }
    }
}
