#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "../GameEngine.hpp"

class GameState {
public:
    virtual void Init(GameEngine* game) = 0;
    virtual void CleanUp() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void ProcessInput(GameEngine* game) = 0;
    virtual void Update(GameEngine* game) = 0;
    virtual void RenderFrame(GameEngine* game) = 0;

    void ChangeState(GameEngine* game, GameState* state) {
        game->ChangeState(state);
    }
protected:
    GameState() {}
};

#endif // GAMESTATE_HPP_INCLUDED
