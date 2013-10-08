#ifndef TITLESTATE_HPP_INCLUDED
#define TITLESTATE_HPP_INCLUDED

#include "GameState.hpp"

class TitleState : public GameState {
public:
    void Init();
    void CleanUp();

    void Pause();
    void Resume();

    void ProcessInput(GameEngine* game);
    void Update(GameEngine* game);
    void RenderFrame(GameEngine* game);

    static TitleState* Instance() {
        return &m_TitleState;
    }

protected:
    TitleState() {}

private:
    static TitleState m_TitleState;
    };

#endif // TITLESTATE_HPP_INCLUDED
