#include "Events.hpp"
#include <iostream> // Temporary

namespace Event {

    /// Test
    Test::Test(int time) : Base(time) {
        debugName = "Test";
    }

    Result Test::ForwardEvent() {
        Result result;
        result.success = true;
        result.msg = "";

        std::cout << "This ForwardEvent should occur just after time " << time << std::endl;

        return result;
    }

    Result Test::BackwardEvent() {
        Result result;
        result.success = true;
        result.msg = "";

        std::cout << "This BackwardEvent should occur just before time " << time << std::endl;

        return result;
    }

    /// PlayerMove
    PlayerMove::PlayerMove(int time, GameObject::Player* player, int xFrom, int yFrom, int xTo, int yTo) : Base(time) {
        debugName = "PlayerMove";
        this->player = player;
        this->xFrom = xFrom;
        this->yFrom = yFrom;
        this->xTo = xTo;
        this->yTo = yTo;
    }

    Result PlayerMove::ForwardEvent() {
        Result result;
        result.success = true;
        result.msg = "";

        if (player->x == xFrom && player->y == yFrom) {
            //TODO: Also check that (xTo,yTo) are free!
            player->x = xTo;
            player->y = yTo;
        } else {
            result.success = false;
            result.msg = "Player was not at (xFrom,yFrom)";
        }

        return result;
    }

    Result PlayerMove::BackwardEvent() {
        Result result;
        result.success = true;
        result.msg = "";

        if (player->x == xTo && player->y == yTo) {
            //TODO: Also check that (xFrom,yFrom) are free!
            player->x = xFrom;
            player->y = yFrom;
        } else {
            result.success = false;
            result.msg = "Player was not at (xTo,yTo)";
        }

        return result;
    }

    /// DoorOpen
    DoorOpen::DoorOpen(int time, GameObject::Door* door, GameObject::Player* player, int xPlayer, int yPlayer) : Base(time) {
        debugName = "DoorOpen";
        this->door = door;
        this->player = player;
        this->xPlayer = xPlayer;
        this->yPlayer = yPlayer;
    }

    Result DoorOpen::ForwardEvent() {
        Result result;
        result.success = true;
        result.msg = "";

        if (player->x == xPlayer && player->y == yPlayer) {
            door->open = true;
        } else {
            result.success = false;
            result.msg = "Player was not at (xPlayer,yPlayer)";
        }

        return result;
    }

    Result DoorOpen::BackwardEvent() {
        Result result;
        result.success = true;
        result.msg = "";

        door->open = false;

        return result;
    }
}
