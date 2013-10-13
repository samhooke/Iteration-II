#include "Events.hpp"
#include <iostream> // Temporary

namespace Event {

    /// Test
    Test::Test(int time) : Base(time) {}

    bool Test::ForwardEvent() {
        std::cout << "This ForwardEvent should occur at: " << time << std::endl;
        return true;
    }

    bool Test::BackwardEvent() {
        std::cout << "This BackwardEvent should occur at: " << time << std::endl;
        return true;
    }

    /// PlayerMove
    PlayerMove::PlayerMove(int time, GameObject::Player* player, int xFrom, int yFrom, int xTo, int yTo) : Base(time) {

    }

    bool PlayerMove::ForwardEvent() {
        return true;
    }

    bool PlayerMove::BackwardEvent() {
        return true;
    }
}
