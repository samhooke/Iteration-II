#ifndef OBJECTSGENERAL_HPP_INCLUDED
#define OBJECTSGENERAL_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

namespace GameObject {
    class Door : public GameObject::Static {
    public:
        void Update();

        Door(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~Door();
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
}

#endif // OBJECTSGENERAL_HPP_INCLUDED