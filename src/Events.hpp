#ifndef EVENTS_HPP_INCLUDED
#define EVENTS_HPP_INCLUDED

#include "EventBase.hpp"
#include "objects/Player.hpp"
#include "objects/ObjectsGeneral.hpp"

namespace Event {

    /// Test
    class Test : public Base {
    public:
        Test(int time);
        Result ForwardEvent();
        Result BackwardEvent();
    };

    /// PlayerMove
    class PlayerMove : public Base {
    public:
        PlayerMove(int time, GameObject::Player* player, int xFrom, int yFrom, int xTo, int yTo);
        Result ForwardEvent();
        Result BackwardEvent();

        GameObject::Player* player;
        int xFrom;
        int yFrom;
        int xTo;
        int yTo;
    };

    /// PlayerExpire
    class PlayerExpire : public PlayerMove {
    public:
        PlayerExpire(int time, GameObject::Player* player, int x, int y);
    };

    /// DoorOpen
    class DoorOpen : public Base {
    public:
        DoorOpen(int time, GameObject::Door* door, GameObject::Player* player, int xPlayer, int yPlayer);
        Result ForwardEvent();
        Result BackwardEvent();

        GameObject::Door* door;
        GameObject::Player* player;
        int xPlayer;
        int yPlayer;
    };
}

#endif // EVENTS_HPP_INCLUDED
