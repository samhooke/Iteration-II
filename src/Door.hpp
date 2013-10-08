#ifndef DOOR_HPP_INCLUDED
#define DOOR_HPP_INCLUDED

#include "ObjectsBase.hpp"

namespace GameObject {
    class Door : public GameObject::Static {
    public:
        void Update();

        Door(unsigned int x, unsigned int y);
        ~Door();
    };
}

#endif // DOOR_HPP_INCLUDED
