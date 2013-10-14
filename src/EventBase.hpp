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
        virtual ~Base();

        std::string debugName = "Undefined debugName (Event::Base)";
        int time;

        virtual Result ForwardEvent() = 0;
        virtual Result BackwardEvent() = 0;
    };
}

#endif // EVENTBASE_HPP_INCLUDED
