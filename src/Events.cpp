#include "Events.hpp"
#include <iostream> // Temporary

namespace Event {

    /// Test
    Test::Test(int time) : Base(time) {}

    bool Test::ForwardEvent() {
        std::cout << "This ForwardEvent should occur just after time " << time << std::endl;
        return true;
    }

    bool Test::BackwardEvent() {
        std::cout << "This BackwardEvent should occur just before time " << time << std::endl;
        return true;
    }

    /// PlayerMove
    PlayerMove::PlayerMove(int time, GameObject::Player* player, int xFrom, int yFrom, int xTo, int yTo) : Base(time) {
        this->player = player;
        this->xFrom = xFrom;
        this->yFrom = yFrom;
        this->xTo = xTo;
        this->yTo = yTo;
    }

    bool PlayerMove::ForwardEvent() {
        bool eventSuccess = true;

        if (player->x == xFrom && player->y == yFrom) {
            //TODO: Also check that (xTo,yTo) are free!
            player->x = xTo;
            player->y = yTo;
        } else {
            eventSuccess = false;
        }

        return eventSuccess;
    }

    bool PlayerMove::BackwardEvent() {
        bool eventSuccess = true;

        if (player->x == xTo && player->y == yTo) {
            //TODO: Also check that (xFrom,yFrom) are free!
            player->x = xFrom;
            player->y = yFrom;
        } else {
            eventSuccess = false;
        }

        return eventSuccess;
    }

    /// DoorOpen
    DoorOpen::DoorOpen(int time, GameObject::Door* door, GameObject::Player* player, int xPlayer, int yPlayer) : Base(time) {
        this->door = door;
        this->player = player;
        this->xPlayer = xPlayer;
        this->yPlayer = yPlayer;
    }

    bool DoorOpen::ForwardEvent() {
        bool eventSuccess = true;

        if (player->x == xPlayer && player->y == yPlayer) {
            door->open = true;
        } else {
            eventSuccess = false;
        }

        return eventSuccess;
    }

    bool DoorOpen::BackwardEvent() {
        bool eventSuccess = true;

        door->open = false;

        return eventSuccess;
    }
}
