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

    /// LinkableStateChange
    class LinkableStateChange : public Base {
    public:
        LinkableStateChange(int time, GameObject::StaticLinkable* linkable, GameObject::Player* player, int xPlayer, int yPlayer, bool stateFrom);
        Result ForwardEvent();
        Result BackwardEvent();

        GameObject::StaticLinkable* linkable;
        GameObject::Player* player;
        int xPlayer;
        int yPlayer;
        bool stateFrom;
        bool stateTo;
    };
}

#endif // EVENTS_HPP_INCLUDED
