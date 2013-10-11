#ifndef TIMEMACHINE_HPP_INCLUDED
#define TIMEMACHINE_HPP_INCLUDED

#include "../ObjectsBase.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"
#include "Player.hpp"

namespace GameObject {
    class TimeMachine : public GameObject::Static {
    public:
        void Update();

        TimeMachine(int x, int y, GameEngine* game, LevelManager* levelManager);
        ~TimeMachine();

        Player* parent;
        int expiryTime;
        void SetNextCloneDetails(GameObject::Player* parent, int expiryTime);
    private:
        float lastActionTime;
        void UpdateDisplayCharacter();
    };
}

#endif // TIMEMACHINE_HPP_INCLUDED
