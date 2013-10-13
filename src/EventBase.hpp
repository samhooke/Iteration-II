#ifndef EVENTBASE_HPP_INCLUDED
#define EVENTBASE_HPP_INCLUDED

namespace Event {
    class Base {
    public:
        Base(int time);

        int time;

        virtual bool ForwardEvent() = 0;
        virtual bool BackwardEvent() = 0;
    };
}

#endif // EVENTBASE_HPP_INCLUDED
