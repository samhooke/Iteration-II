#ifndef EVENTBASE_HPP_INCLUDED
#define EVENTBASE_HPP_INCLUDED

#include <string>

// Front events are ordered first, then middle, then back
#define EVENT_ORDER_FRONT -1
#define EVENT_ORDER_MIDDLE 0
#define EVENT_ORDER_BACK 1

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
        int order = EVENT_ORDER_MIDDLE;

        virtual Result ForwardEvent() = 0;
        virtual Result BackwardEvent() = 0;

        void SetFailOnPlayerPos(bool failOnPlayerPos);
        bool failOnPlayerPos = true;
    };
}

#endif // EVENTBASE_HPP_INCLUDED
