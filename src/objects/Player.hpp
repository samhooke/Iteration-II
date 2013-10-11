#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

namespace GameObject {
    class Player : public Dynamic {
    public:
        void Update();
        void UpdateTimeChanged();

        Player(int x, int y, GameEngine* game, LevelManager* levelManager, bool original, GameObject::Player* parent, int expiryTime);
        ~Player();

        char cloneDesignation;  // The letter assigned to this particular clone
        bool original;          // True if this was the first Player
        Player* parent;         // Reference to the Player that made us
        int expiryTime;         // The time this Player was sent back in time (and so, the time it stops existing)
    private:
        float lastActionTime;
        void UpdateDisplayCharacter();
    };
}

#endif // PLAYER_HPP_INCLUDED
