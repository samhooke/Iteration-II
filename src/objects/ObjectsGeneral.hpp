#ifndef OBJECTSGENERAL_HPP_INCLUDED
#define OBJECTSGENERAL_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

namespace GameObject {
    class Door : public GameObject::StaticLinkable {
    public:
        void Update();

        Door(int x, int y, GameEngine* game, LevelManager* levelManager, bool requiresKey, bool state);
        ~Door();

        bool requiresKey = false;

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

    class Lever : public GameObject::StaticLinkable {
    public:
        void Update();

        Lever(int x, int y, GameEngine* game, LevelManager* levelManager, bool state);
        ~Lever();

        void UpdateSprite();
    };

    class PressurePlate : public GameObject::StaticLinkable {
    public:
        void Update();

        PressurePlate(int x, int y, GameEngine* game, LevelManager* levelManager, bool state);
        ~PressurePlate();

        void UpdateSprite();
        void UpdateTimeChanged();
    };
}

#endif // OBJECTSGENERAL_HPP_INCLUDED
