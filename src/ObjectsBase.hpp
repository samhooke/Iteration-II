#ifndef OBJECTSBASE_HPP_INCLUDED
#define OBJECTSBASE_HPP_INCLUDED

#include "Tiles.hpp"

//unsigned int x = 0;
//unsigned int y = 0;
//int displayCharacter = TILE_QUESTION;

namespace GameObject {
    class Base {
    public:
        virtual void Update() = 0;
        int displayCharacter;

        unsigned int x;
        unsigned int y;
    };

    // Objects that remain fixed
    class Static : public Base {
    };

    // Objects that can move
    class Dynamic : public Base {
    };
}
#endif // OBJECTSBASE_HPP_INCLUDED
