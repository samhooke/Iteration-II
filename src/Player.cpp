#include "Player.hpp"

namespace GameObject {
    Player::Player(unsigned int x, unsigned int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_FACE_OUTLINE;
    }

    Player::~Player() {}

    void Player::Update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            SetPosRelative(-1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            SetPosRelative(+1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            SetPosRelative(0, -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            SetPosRelative(0, +1);
    }
}
