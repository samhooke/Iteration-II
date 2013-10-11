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
                bool key_action_1 = sf::Keyboard::isKeyPressed(INPUT_ACTION_1);
                bool key_action_2 = sf::Keyboard::isKeyPressed(INPUT_ACTION_2);
                if (key_action_1) {
                    // IMPORTANT: This code almost always runs immediately when the player gets into the time machine
                    // This is only because the INPUT_ACTION_1 key is still pressed, which triggers this event
                    // This is not a safe, reliable way to handle this and should be changed!

                    // Go back in time
                    lastActionTime = game->gameClock->getElapsedTime().asSeconds();
                    levelManager->iterationData->Backward();
                } else if (key_action_2) {
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
