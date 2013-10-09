#include "Radiation.hpp"

namespace GameObject {
    // RadiationWeak
    RadiationWeak::RadiationWeak(int x, int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_RADIATION_WEAK;
    }

    RadiationWeak::~RadiationWeak() {}

    void RadiationWeak::Update() {}

    // RadiationStrong
    RadiationStrong::RadiationStrong(int x, int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_RADIATION_STRONG;
    }

    RadiationStrong::~RadiationStrong() {}

    void RadiationStrong::Update() {}
}
