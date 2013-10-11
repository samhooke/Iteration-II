#include "TimeMachine.hpp"
#include "../LevelData.hpp"
#include "../Tiles.hpp"
#include "../IterationData.hpp"
#include "../Defs.hpp"

namespace GameObject {
    TimeMachine::TimeMachine(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        UpdateDisplayCharacter();
    }

    TimeMachine::~TimeMachine() {}

    void TimeMachine::Update() {
        UpdateDisplayCharacter();
        if (Controlling()) {
            if (game->controls->GetKeyDelaySufficient()) {
                bool keyAction1 = game->controls->GetKey(InputKey::Action1);
                bool keyAction2 = game->controls->GetKey(InputKey::Action2);
                if (keyAction1 && levelManager->iterationData->CanGoBackward()) {
                    // Go back in time
                    levelManager->iterationData->GoBackward();
                    game->controls->ResetKeyDelay();
                } else if (keyAction2) {
                    // Exit time machine (create new player and pass control to them)
                    levelManager->levelData->CreatePlayer(x, y, true, parent, expiryTime); //TODO: Fill in parent and expiryTime
                    hasControl = false;
                    game->controls->ResetKeyDelay();
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

    void TimeMachine::SetNextCloneDetails(GameObject::Player* parent, int expiryTime) {
        this->parent = parent;
        this->expiryTime = expiryTime;
    }
}
