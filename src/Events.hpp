#ifndef EVENTS_HPP_INCLUDED
#define EVENTS_HPP_INCLUDED

#include "EventBase.hpp"
#include "objects/Player.hpp"

namespace Event {

    class Test : public Base {
    public:
        Test(int time);
        bool Event();
    };

    class PlayerMove : public Base {
    public:
        PlayerMove(int time, GameObject::Player* player, int xFrom, int yFrom, int xTo, int yTo);
        bool Event();
    };
}

#endif // EVENTS_HPP_INCLUDED
