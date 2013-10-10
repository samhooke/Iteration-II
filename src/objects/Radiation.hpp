#ifndef RADIATION_HPP_INCLUDED
#define RADIATION_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

namespace GameObject {
    class RadiationWeak : public GameObject::Static {
    public:
        void Update();

        RadiationWeak(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~RadiationWeak();
    };

    class RadiationStrong : public GameObject::Static {
    public:
        void Update();

        RadiationStrong(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~RadiationStrong();
    };
}

#endif // RADIATION_HPP_INCLUDED
