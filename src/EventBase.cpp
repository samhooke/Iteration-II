#include "EventBase.hpp"

namespace Event {
    Base::Base(int time) {
        this->time = time;
    }

    Base::~Base() {
        // Non-virtual destructor required to avoid undefined behaviour upon deletion
    }

    // Used to disable ForwardEvent() and BackwardEvent() failing when the player
    // is at the wrong position. This is used by Player::CreateFutureRepercussions()
    void Base::SetFailOnPlayerPos(bool failOnPlayerPos) {
        this->failOnPlayerPos = failOnPlayerPos;
    }
}
