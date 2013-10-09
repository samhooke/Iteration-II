#ifndef DOOR_HPP_INCLUDED
#define DOOR_HPP_INCLUDED

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
}

#endif // DOOR_HPP_INCLUDED
