#include "Radiation.hpp"

namespace GameObject {
    Radiation::Radiation(int x, int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_RADIATION;
    }

    Radiation::~Radiation() {}

    void Radiation::Update() {}
}
