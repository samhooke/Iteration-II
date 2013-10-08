#include "Door.hpp"

namespace GameObject {
    Door::Door(unsigned int x, unsigned int y) {
        this->x = x;
        this->y = y;
        displayCharacter = TILE_DOOR;
    }

    Door::~Door() {}

    void Door::Update() {}
}
