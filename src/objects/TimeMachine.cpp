#include "TimeMachine.hpp"

namespace GameObject {
    TimeMachine::TimeMachine(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        displayCharacter = TILE_TIMEMACHINE;
    }

    TimeMachine::~TimeMachine() {}

    void TimeMachine::Update() {}
}
