#ifndef TITLESTATE_HPP_INCLUDED
#define TITLESTATE_HPP_INCLUDED

#include "GameState.hpp"
#include "../GameEngine.hpp"

class TitleState : public GameState {
public:
    void Init(GameEngine* game);
    void CleanUp(GameEngine* game);

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

    sf::Clock clock;

    int memCount = 0;
    int memCountMax = 32768;
    int memCountStep = 2048;
    float memCountTimeLastStep;

    int dotCount[4];
    float dotTime[4];

    int progressCount[2];
    int progressTime[2];
    };

#endif // TITLESTATE_HPP_INCLUDED
