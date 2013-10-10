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
                bool key_action2 = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
                if (key_action) {
                    // Go back in time
                    lastActionTime = game->gameClock->getElapsedTime().asSeconds();
                    levelManager->iterationData->Backward();
                } else if (key_action2) {
                    // Exit time machine (create new player and pass control to them)
                    levelManager->levelData->CreatePlayer(x, y, true);
                    hasControl = false;
                }
            }
        }
    }
}
