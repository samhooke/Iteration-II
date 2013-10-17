#ifndef PLAYSTATE_HPP_INCLUDED
#define PLAYSTATE_HPP_INCLUDED

#include "GameState.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

class PlayState : public GameState {
public:
    void Init(GameEngine* game);
    void CleanUp();

    void Pause();
    void Resume();

    void ProcessInput(GameEngine* game);
    void Update(GameEngine* game);
    void RenderFrame(GameEngine* game);

    static PlayState* Instance() {
        return &m_PlayState;
    }
protected:
    PlayState() {}

private:
    static PlayState m_PlayState;

    LevelManager* levelManager;
};

#endif // PLAYSTATE_HPP_INCLUDED
