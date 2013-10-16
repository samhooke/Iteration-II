#ifndef EVENTS_HPP_INCLUDED
#define EVENTS_HPP_INCLUDED

#include "EventBase.hpp"
#include "objects/Player.hpp"
#include "objects/ObjectsGeneral.hpp"

class LevelData;

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

    /// PlayerDie_Linkable
    class PlayerDie_Linkable : public Base {
    public:
        PlayerDie_Linkable(int time, GameObject::Player* player, int x, int y, GameObject::StaticLinkable* killer, int xKiller, int yKiller, bool stateKiller);
        Result ForwardEvent();
        Result BackwardEvent();

        GameObject::Player* player;
        int xPlayer;
        int yPlayer;
        GameObject::StaticLinkable* killer;
        int xKiller;
        int yKiller;
        bool stateKiller;
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

    /// LinkableKillAllPlayersAt
    class LinkableKillAllPlayersAt : public Base {
    public:
        LinkableKillAllPlayersAt(int time, LevelData* levelData, GameObject::StaticLinkable* linkable, int x, int y, bool stateForward, bool stateBackward);
        Result ForwardEvent();
        Result BackwardEvent();

        LevelData* levelData;
        GameObject::StaticLinkable* linkable;
        int x;
        int y;
        bool stateForward;
        bool stateBackward;
    };
}

#endif // EVENTS_HPP_INCLUDED
