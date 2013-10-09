#include "Door.hpp"

namespace GameObject {
    Door::Door(int x, int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_DOOR;
    }

    Door::~Door() {}

    void Door::Update() {}
}
