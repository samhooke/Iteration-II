#include "Events.hpp"
#include <iostream>
#include <sstream>

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
            std::ostringstream msg;
            msg << "Player (" << player->cloneDesignation << ") was not at (xFrom:" << xFrom << ",yFrom:" << yFrom << ")";
            result.msg = msg.str();
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
            std::ostringstream msg;
            msg << "Player (" << player->cloneDesignation << ") was not at (xTo:" << xTo << ",yTo:" << yTo << ")";
            result.msg = msg.str();
        }

        return result;
    }

    /// PlayerExpire
    PlayerExpire::PlayerExpire(int time, GameObject::Player* player, int xFrom, int yFrom) : PlayerMove(time, player, xFrom, yFrom, -1, -1) {
        debugName = "PlayerExpire";
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
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xPlayer && player->y == yPlayer) {
            if (door->open != true) {
                door->open = true;
                result.success = true;
            } else {
                msg << "Door was already open";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }

    Result DoorOpen::BackwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xPlayer && player->y == yPlayer) {
            if (door->open != false) {
                door->open = false;
                result.success = true;
            } else {
                msg << "Door was already shut";

            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }

    /// LeverPull
    LeverPull::LeverPull(int time, GameObject::Lever* lever, GameObject::Player* player, int xPlayer, int yPlayer, bool stateFrom, bool stateTo) : Base(time) {
        this->lever = lever;
        this->player = player;
        this->xPlayer = xPlayer;
        this->yPlayer = yPlayer;
        this->stateFrom = stateFrom;
        this->stateTo = stateTo;
    }

    Result LeverPull::ForwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xPlayer && player->y == yPlayer) {
            if (lever->state == stateFrom) {
                lever->state = stateTo;
                result.success = true;
            } else {
                msg << "Lever was not in the expected state (stateFrom:" << stateFrom << ")";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }

    Result LeverPull::BackwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xPlayer && player->y == yPlayer) {
            if (lever->state == stateTo) {
                lever->state = stateFrom;
                result.success = true;
            } else {
                msg << "Lever was not in the expected state (stateTo:" << stateTo << ")";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }
}
