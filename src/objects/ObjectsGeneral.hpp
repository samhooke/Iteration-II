#ifndef OBJECTSGENERAL_HPP_INCLUDED
#define OBJECTSGENERAL_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

namespace GameObject {
    class Door : public GameObject::Static {
    public:
        void Update();

        Door(int x, int y, GameEngine* game, LevelManager* levelManager, bool requiresKey);
        ~Door();

        bool requiresKey = false;
        bool open = false;

        void UpdateSprite();
    };

    class Window : public GameObject::Static {
    public:
        void Update();

        Window(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~Window();
    };

    class Terminal : public GameObject::Static {
    public:
        void Update();

        Terminal(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~Terminal();
    };

    class Lever : public GameObject::Static {
    public:
        void Update();

        Lever(int x, int y, GameEngine* game, LevelManager* levelManager, bool state);
        ~Lever();

        bool state = false;

        void UpdateSprite();
    };
}

#endif // OBJECTSGENERAL_HPP_INCLUDED
