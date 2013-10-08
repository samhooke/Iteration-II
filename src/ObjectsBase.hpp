#ifndef OBJECTSBASE_HPP_INCLUDED
#define OBJECTSBASE_HPP_INCLUDED

#include "Tiles.hpp"
#include "GameEngine.hpp"

namespace GameObject {
    class Base {
    public:
        virtual void Update() = 0;

        GameEngine* game;

        unsigned int x;
        unsigned int y;
        int displayCharacter;
    };

    // Objects that remain fixed
    class Static : public Base {
    };

    // Objects that can move
    class Dynamic : public Base {
    public:
        bool SetPos(unsigned int x, unsigned int y);
        bool SetPosRelative(unsigned int x, unsigned int y);
    };
}
#endif // OBJECTSBASE_HPP_INCLUDED
