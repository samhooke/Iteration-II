#include "Door.hpp"

namespace GameObject {
    Door::Door(unsigned int x, unsigned int y, GameEngine* game) {
        this->x = x;
        this->y = y;
        this->game = game;
        displayCharacter = TILE_DOOR;
    }

    Door::~Door() {}

    void Door::Update() {}
}
