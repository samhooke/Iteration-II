#include "Radiation.hpp"

namespace GameObject {
    // RadiationWeak
    RadiationWeak::RadiationWeak(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        displayCharacter = TILE_RADIATION_WEAK;
    }

    RadiationWeak::~RadiationWeak() {}

    void RadiationWeak::Update() {}

    // RadiationStrong
    RadiationStrong::RadiationStrong(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        displayCharacter = TILE_RADIATION_STRONG;
    }

    RadiationStrong::~RadiationStrong() {}

    void RadiationStrong::Update() {}
}
