#include "EventBase.hpp"

namespace Event {
    Base::Base(int time) {
        this->time = time;
    }

    Base::~Base() {
        // Non-virtual destructor required to avoid undefined behaviour upon deletion
    }
}
