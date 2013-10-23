#ifndef OBJECTSBASE_HPP_INCLUDED
#define OBJECTSBASE_HPP_INCLUDED

#include <string>
#include <map>
#include "objects/Tags.hpp"
#include "Tiles.hpp"
#include "GameEngine.hpp"

class LevelManager; // To avoid #include loop between ObjectsBase.hpp and LevelManager.hpp

namespace GameObject {

    struct TimeData {
        int x = -1;
        int y = -1;
        bool exists = false;
    };

    class Base {
    public:
        virtual ~Base();

        virtual void Update() = 0;
        virtual void UpdateTimeChanged();

        GameEngine* game;
        LevelManager* levelManager;

        std::string debugName = "Undefined debugName (GameObject::Base)";
        std::string tag = TAG_DEFAULT;
        int x;
        int y;
        int displayCharacter;
        bool canHaveControl = false;
        bool hasControl = false;

        bool Controlling();

        bool IsPosFree(int x, int y, bool checkObjects = false);       // Checks only against tiles (wall, floor, restricted)
        int GetObjectIndexAtPosWithTag(int x, int y, std::string tag);
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
        void TimeDataWrite(bool exists);    // Update the timeData for our current time
        bool TimeDataAvailable();           // Returns true if timeData is available for currentTime. Must be called before TimeDataRead()
        TimeData TimeDataRead();            // Read the timeData for our current time

        bool useCollisionDetection = true;

        bool SetPos(int x, int y);          // Jumps to position x,y if IsPosFree
        bool SetPosRelative(int x, int y);  // Moves relative to current position by x,y if IsPosFree
    };

    class StaticLinkable : public Static {
    public:
        StaticLinkable(int x, int y, GameEngine* game, LevelManager* levelManager, bool state);

        bool state;
    };
}
#endif // OBJECTSBASE_HPP_INCLUDED
