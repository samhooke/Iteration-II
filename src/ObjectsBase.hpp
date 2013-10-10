#ifndef OBJECTSBASE_HPP_INCLUDED
#define OBJECTSBASE_HPP_INCLUDED

#include "Tiles.hpp"
#include "GameEngine.hpp"

class LevelManager; // To avoid #include loop between ObjectsBase.hpp and LevelManager.hpp

namespace GameObject {
    class Base {
    public:
        virtual ~Base();

        virtual void Update() = 0;

        GameEngine* game;
        LevelManager* levelManager;

        int x;
        int y;
        int displayCharacter;
    };

    // Objects that remain fixed
    class Static : public Base {
    public:
        Static(int x, int y, GameEngine* game, LevelManager* levelManager);
    };

    // Objects that can move
    class Dynamic : public Base {
    public:
        Dynamic(int x, int y, GameEngine* game, LevelManager* levelManager);

        bool useCollisionDetection = true;

        bool SetPos(int x, int y);
        bool SetPosRelative(int x, int y);
        bool IsPosFree(int x, int y);
    };
}
#endif // OBJECTSBASE_HPP_INCLUDED
