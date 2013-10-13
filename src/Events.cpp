#include "Events.hpp"
#include <iostream> // Temporary

namespace Event {

    /// Test
    Test::Test(int time) : Base(time) {}

    bool Test::Event() {
        std::cout << "This test event should occur at: " << time << std::endl;
        return true;
    }

    /// PlayerMove
    PlayerMove::PlayerMove(int time, GameObject::Player* player, int xFrom, int yFrom, int xTo, int yTo) : Base(time) {

    }

    bool PlayerMove::Event() {
        return true;
    }
}
