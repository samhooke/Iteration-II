#ifndef OBJECTSGENERAL_HPP_INCLUDED
#define OBJECTSGENERAL_HPP_INCLUDED

#include "ObjectsBase.hpp"
#include "GameEngine.hpp"
#include "LevelData.hpp"

namespace GameObject {
    class Door : public GameObject::Static {
    public:
        void Update();

        Door(int x, int y, GameEngine* game, LevelData* levelData);
        ~Door();
    };

    class Window : public GameObject::Static {
    public:
        void Update();

        Window(int x, int y, GameEngine* game, LevelData* levelData);
        ~Window();
    };
}

#endif // OBJECTSGENERAL_HPP_INCLUDED
