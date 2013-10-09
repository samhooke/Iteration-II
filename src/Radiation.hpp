#ifndef RADIATION_HPP_INCLUDED
#define RADIATION_HPP_INCLUDED

#include "ObjectsBase.hpp"
#include "GameEngine.hpp"
#include "LevelData.hpp"

namespace GameObject {
    class Radiation : public GameObject::Static {
    public:
        void Update();

        Radiation(int x, int y, GameEngine* game, LevelData* levelData);
        ~Radiation();
    };
}

#endif // RADIATION_HPP_INCLUDED
