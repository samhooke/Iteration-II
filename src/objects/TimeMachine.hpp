#ifndef TIMEMACHINE_HPP_INCLUDED
#define TIMEMACHINE_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

namespace GameObject {
    class TimeMachine : public GameObject::Static {
    public:
        void Update();

        TimeMachine(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~TimeMachine();
    };
}

#endif // TIMEMACHINE_HPP_INCLUDED
