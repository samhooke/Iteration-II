#ifndef DOOR_HPP_INCLUDED
#define DOOR_HPP_INCLUDED

#include "ObjectsBase.hpp"
#include "GameEngine.hpp"

namespace GameObject {
    class Door : public GameObject::Static {
    public:
        void Update();

        Door(unsigned int x, unsigned int y, GameEngine* game);
        ~Door();
    };
}

#endif // DOOR_HPP_INCLUDED
