#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "ObjectsBase.hpp"

namespace GameObject {
    class Player : public Dynamic {
    public:
        void Update();

        Player(unsigned int x, unsigned int y);
        ~Player();
    };
}

#endif // PLAYER_HPP_INCLUDED
