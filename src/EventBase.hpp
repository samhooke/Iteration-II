#ifndef EVENTBASE_HPP_INCLUDED
#define EVENTBASE_HPP_INCLUDED

#include <string>

namespace Event {
    struct Result {
        bool success;
        std::string msg;
    };

    class Base {
    public:
        Base(int time);

        std::string debugName = "No debugName set";
        int time;

        virtual Result ForwardEvent() = 0;
        virtual Result BackwardEvent() = 0;
    };
}

#endif // EVENTBASE_HPP_INCLUDED
