#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

namespace GameObject {
    class Player : public Dynamic {
    public:
        void Update();

        Player(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~Player();
    private:
        float lastMovedTime;
    };
}

#endif // PLAYER_HPP_INCLUDED
