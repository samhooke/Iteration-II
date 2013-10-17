#include "Events.hpp"
#include <iostream>
#include <sstream>

#include <vector>
#include "LevelData.hpp"
#include "objects/Player.hpp"

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
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xFrom && player->y == yFrom) {
            if (player->IsPosFree(xTo, yTo) || (xTo == -1 && yTo == -1)) {
                player->x = xTo;
                player->y = yTo;
                result.success = true;
            } else {
                msg << "Position (xTo:" << xTo << ",yTo:" << yTo << ") was not free";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xFrom:" << xFrom << ",yFrom:" << yFrom << ")";
        }

        result.msg = msg.str();
        return result;
    }

    Result PlayerMove::BackwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xTo && player->y == yTo) {
            if (player->IsPosFree(xFrom, yFrom) || (xFrom == -1 && yFrom == -1)) {
                player->x = xFrom;
                player->y = yFrom;
                result.success = true;
            } else {
                msg << "Position (xFrom:" << xFrom << ",yFrom:" << yFrom << ") was not free";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xTo:" << xTo << ",yTo:" << yTo << ")";
        }

        result.msg = msg.str();
        return result;
    }

    /// PlayerExpire
    PlayerExpire::PlayerExpire(int time, GameObject::Player* player, int xFrom, int yFrom) : PlayerMove(time, player, xFrom, yFrom, -1, -1) {
        debugName = "PlayerExpire";
    }

    ///PlayerDie_Linkable
    PlayerDie_Linkable::PlayerDie_Linkable(int time, GameObject::Player* player, int xPlayer, int yPlayer, GameObject::StaticLinkable* killer, int xKiller, int yKiller, bool stateKiller) : Base(time) {
        debugName = "PlayerDie_Linkable";
        this->player = player;
        this->xPlayer = xPlayer;
        this->yPlayer = yPlayer;
        this->killer = killer;
        this->xKiller = xKiller;
        this->yKiller = yKiller;
        this->stateKiller = stateKiller;
    }

    Result PlayerDie_Linkable::ForwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xPlayer && player->y == yPlayer) {
            if (killer->x == xKiller && killer->y == yKiller) {
                if (killer->state == stateKiller) {
                    if (player->dead == false) {
                        player->dead = true;
                        result.success = true;
                    } else {
                        msg << "Player (" << player->cloneDesignation << ") was already dead";
                    }
                } else {
                    msg << "Killer was not in expected state (stateKiller:" << stateKiller << ")";
                }
            } else {
                msg << "Killer was not at (xKiller:" << xKiller << ",yKiller:" << yKiller << ")";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }

    Result PlayerDie_Linkable::BackwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (player->x == xPlayer && player->y == yPlayer) {
            if (killer->x == xKiller && killer->y == yKiller) {
                if (killer->state == stateKiller) {
                    if (player->dead == true) {
                        player->dead = false;
                        result.success = true;
                    } else {
                        msg << "Player (" << player->cloneDesignation << ") was already alive";
                    }
                } else {
                    msg << "Killer was not in expected state (stateKiller:" << stateKiller << ")";
                }
            } else {
                msg << "Killer was not at (xKiller:" << xKiller << ",yKiller:" << yKiller << ")";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }

    /// LinkableStateChange
    LinkableStateChange::LinkableStateChange(int time, GameObject::StaticLinkable* linkable, GameObject::Player* player, int xPlayer, int yPlayer, bool stateFrom) : Base(time) {
        debugName = "LinkableStateChange";
        this->linkable = linkable;
        this->player = player;
        this->xPlayer = xPlayer;
        this->yPlayer = yPlayer;
        this->stateFrom = stateFrom;
        this->stateTo = !stateFrom;
    }

    Result LinkableStateChange::ForwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if ((player->x == xPlayer && player->y == yPlayer) || !failOnPlayerPos) {
            if (linkable->state == stateFrom) {
                linkable->state = stateTo;
                result.success = true;
            } else {
                msg << "StaticLinkable was not in the expected state (stateFrom:" << stateFrom << ")";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }

    Result LinkableStateChange::BackwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if ((player->x == xPlayer && player->y == yPlayer) || !failOnPlayerPos) {
            if (linkable->state == stateTo) {
                linkable->state = stateFrom;
                result.success = true;
            } else {
                msg << "StaticLinkable was not in the expected state (stateTo:" << stateTo << ")";
            }
        } else {
            msg << "Player (" << player->cloneDesignation << ") was not at (xPlayer:" << xPlayer << ",yPlayer:" << yPlayer << ")";
        }

        result.msg = msg.str();
        return result;
    }

    /// LinkableKillAllPlayersAt
    LinkableKillAllPlayersAt::LinkableKillAllPlayersAt(int time, LevelData* levelData, GameObject::StaticLinkable* linkable, int x, int y, bool stateForward, bool stateBackward) : Base(time) {
        debugName = "LinkableKillAllPlayersAt";
        this->levelData = levelData;
        this->linkable = linkable;
        this->x = x;
        this->y = y;
        this->stateForward = stateForward;
        this->stateBackward = stateBackward;
    }

    Result LinkableKillAllPlayersAt::ForwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (linkable->state == stateForward) {
            result.success = true;
            std::vector<GameObject::Player*> players = levelData->GetListOfAllPlayers();
            for (int i = 0; i < (int)players.size(); i++) {
                if (players[i]->x == x && players[i]->y == y) {
                    // Kill the player
                    if (players[i]->dead == false)
                        players[i]->dead = true;
                }
            }
        } else {
            msg << "StaticLinkable was not in the expected state (stateForward:" << stateForward << ")";
        }

        result.msg = msg.str();
        return result;
    }

    Result LinkableKillAllPlayersAt::BackwardEvent() {
        Result result;
        result.success = false;
        result.msg = "";
        std::ostringstream msg;

        if (linkable->state == stateBackward) {
            result.success = true;
            std::vector<GameObject::Player*> players = levelData->GetListOfAllPlayers();
            for (int i = 0; i < (int)players.size(); i++) {
                if (players[i]->x == x && players[i]->y == y) {
                    // Revive the player
                    if (players[i]->dead == true)
                        players[i]->dead = false;
                }
            }
        } else {
            msg << "StaticLinkable was not in the expected state (stateBackward:" << stateBackward << ")";
        }

        result.msg = msg.str();
        return result;
    }
}
