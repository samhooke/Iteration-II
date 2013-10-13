#ifndef EVENTBASE_HPP_INCLUDED
#define EVENTBASE_HPP_INCLUDED

namespace Event {
    class Base {
    public:
        Base(int time);

        int time;

        virtual bool Event() = 0;
    };
}

#endif // EVENTBASE_HPP_INCLUDED
