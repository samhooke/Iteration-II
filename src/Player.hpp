#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "ObjectsBase.hpp"
#include "GameEngine.hpp"
#include "LevelData.hpp"

namespace GameObject {
    class Player : public Dynamic {
    public:
        void Update();

        Player(unsigned int x, unsigned int y, GameEngine* game, LevelData* levelData);
        ~Player();
    private:
        float lastMovedTime;
    };
}

#endif // PLAYER_HPP_INCLUDED
