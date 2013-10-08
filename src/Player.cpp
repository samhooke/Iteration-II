#include "Player.hpp"
#include "Defs.hpp"

namespace GameObject {
    Player::Player(unsigned int x, unsigned int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_FACE_OUTLINE;

        lastMovedTime = game->gameClock->getElapsedTime().asSeconds();
    }

    Player::~Player() {}

    void Player::Update() {

        bool moved = false;

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
        }

        if (moved)
            lastMovedTime = game->gameClock->getElapsedTime().asSeconds();
    }
}
