#include "TimeMachine.hpp"
#include "../IterationData.hpp"

namespace GameObject {
    TimeMachine::TimeMachine(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        displayCharacter = TILE_TIMEMACHINE;

        lastActionTime = game->gameClock->getElapsedTime().asSeconds();
    }

    TimeMachine::~TimeMachine() {}

    void TimeMachine::Update() {
        if (Controlling()) {
            if (game->gameClock->getElapsedTime().asSeconds() > lastActionTime + MOVEMENT_DELAY) {
                bool key_action = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
                if (key_action) {
                    lastActionTime = game->gameClock->getElapsedTime().asSeconds();
                    levelManager->iterationData->Backward();
                }
            }
        }
    }
}
