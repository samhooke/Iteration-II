#include "Player.hpp"
#include "Tags.hpp"
#include "../Defs.hpp"
#include <iostream> // Temporary

namespace GameObject {
    Player::Player(int x, int y, GameEngine* game, LevelManager* levelManager) : Dynamic(x, y, game, levelManager) {
        displayCharacter = TILE_FACE_OUTLINE;

        lastMovedTime = game->gameClock->getElapsedTime().asSeconds();
    }

    Player::~Player() {}

    void Player::Update() {

        bool moved, performedAction = false;

        if (game->gameClock->getElapsedTime().asSeconds() > lastMovedTime + MOVEMENT_DELAY) {


            bool key_l = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            bool key_r = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
            bool key_u = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            bool key_d = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

            int key_mask = (int)key_l | ((int)key_r << 1) | ((int) key_u << 2) | ((int) key_d << 3);

            switch (key_mask) {
            case 0b0001:    moved = SetPosRelative(-1, 0);  break;
            case 0b0010:    moved = SetPosRelative(+1, 0);  break;
            case 0b0100:    moved = SetPosRelative(0, -1);  break;
            case 0b1000:    moved = SetPosRelative(0, +1);  break;
            }

            // Only perform an action if a movement has not occured, to avoid two events happening in one frame
            if (!moved) {
                bool key_action = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
                if (key_action) {
                    if (ObjectAtPosWithTag(x, y, TAG_TIMEMACHINE)) {
                        std::cout << "I try to use the time machine" << std::endl;
                        performedAction = true;
                    }
                }
            }
        }

        if (moved || performedAction) {
            lastMovedTime = game->gameClock->getElapsedTime().asSeconds();
            levelManager->iterationData->Forward();
        }
    }
}
