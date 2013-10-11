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

                bool key_l = sf::Keyboard::isKeyPressed(INPUT_LEFT);
                bool key_r = sf::Keyboard::isKeyPressed(INPUT_RIGHT);
                bool key_u = sf::Keyboard::isKeyPressed(INPUT_UP);
                bool key_d = sf::Keyboard::isKeyPressed(INPUT_DOWN);

                int key_mask = (int)key_l | ((int)key_r << 1) | ((int) key_u << 2) | ((int) key_d << 3);

                bool moved = false;
                switch (key_mask) {
                    case 0b0001:    moved = SetPosRelative(-1, 0);  break;
                    case 0b0010:    moved = SetPosRelative(+1, 0);  break;
                    case 0b0100:    moved = SetPosRelative(0, -1);  break;
                    case 0b1000:    moved = SetPosRelative(0, +1);  break;
                }

                if (moved)
                    goForwardOne = true;

                // Only perform an action if a movement has not occured, to avoid two events happening in one frame
                if (!moved) {
                    bool key_action_1 = sf::Keyboard::isKeyPressed(INPUT_ACTION_1);
                    bool key_action_2 = sf::Keyboard::isKeyPressed(INPUT_ACTION_2);
                    if (key_action_1) {
                        // Perform action with objects we are on
                        int index = GetObjectIndexAtPosWithTag(x, y, TAG_TIMEMACHINE);
                        if (index >= 0) {
                            // Pass control to time machine
                            hasControl = false;
                            levelManager->levelData->SetObjectHasControl(index, true);
                        }
                    } else if (key_action_2) {
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
