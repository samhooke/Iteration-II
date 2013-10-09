#ifndef OBJECTSBASE_HPP_INCLUDED
#define OBJECTSBASE_HPP_INCLUDED

#include "Tiles.hpp"
#include "GameEngine.hpp"

class LevelData; // To avoid #include loop between ObjectsBase.hpp and LevelData.hpp

namespace GameObject {
    class Base {
    public:
        virtual ~Base();

        virtual void Update() = 0;

        GameEngine* game;
        LevelData* levelData;

        int x;
        int y;
        int displayCharacter;
    };

    // Objects that remain fixed
    class Static : public Base {
    };

    // Objects that can move
    class Dynamic : public Base {
    public:
        bool useCollisionDetection = true;

        bool SetPos(int x, int y);
        bool SetPosRelative(int x, int y);
        bool IsPosFree(int x, int y);
    };
}
#endif // OBJECTSBASE_HPP_INCLUDED
