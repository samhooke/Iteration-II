#include "Player.hpp"

namespace GameObject {
    Player::Player(unsigned int x, unsigned int y) {
        this->x = x;
        this->y = y;
        displayCharacter = TILE_FACE_OUTLINE;
    }

    Player::~Player() {}

    void Player::Update() {}
}
