#ifndef OBJECTSBASE_HPP_INCLUDED
#define OBJECTSBASE_HPP_INCLUDED

#include <string>
#include <map>
#include "Tiles.hpp"
#include "GameEngine.hpp"

class LevelManager; // To avoid #include loop between ObjectsBase.hpp and LevelManager.hpp

namespace GameObject {

    struct TimeData {
        int x;
        int y;
    };

    class Base {
    public:
        virtual ~Base();

        virtual void Update() = 0;
        virtual void UpdateTimeChanged();

        GameEngine* game;
        LevelManager* levelManager;

        std::string tag = "Undefined";
        int x;
        int y;
        int displayCharacter;
        bool canHaveControl = false;
        bool hasControl = false;

        bool Controlling();
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

        std::map<int, TimeData> timeData;   // Key/value pairs for storing time data
        void TimeDataWrite();               // Update the timeData for our current time
        TimeData TimeDataRead();            // Read the timeData for our current time

        bool useCollisionDetection = true;

        bool SetPos(int x, int y);          // Jumps to position x,y if IsPosFree
        bool SetPosRelative(int x, int y);  // Moves relative to current position by x,y if IsPosFree
        bool IsPosFree(int x, int y);       // Checks only against tiles (wall, floor, restricted)

        int GetObjectIndexAtPosWithTag(int x, int y, std::string tag);
    };
}
#endif // OBJECTSBASE_HPP_INCLUDED
