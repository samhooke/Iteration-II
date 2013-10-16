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
        bool dead;              // True if dead
        Player* parent;         // Reference to the Player that made us
        int expiryTime;         // The time this Player was sent back in time (and so, the time it stops existing)
        int creationTime;       // The time this Player was created (used by Timeline)
    private:
        float lastActionTime;
        void UpdateDisplayCharacter();

        bool ExpiresThisFrame(); // True if it is our expiryTime this (time)
        bool ExpiresNextFrame(); // True if it is our expiryTime this (time + 1)
    };
}

#endif // PLAYER_HPP_INCLUDED
