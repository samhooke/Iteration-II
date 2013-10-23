#ifndef ENTRYSTATE_HPP_INCLUDED
#define ENTRYSTATE_HPP_INCLUDED

#include "GameState.hpp"
#include "../GameEngine.hpp"

class EntryState : public GameState {
public:
    void Init(GameEngine* game);
    void CleanUp(GameEngine* game);

    void Pause();
    void Resume();

    void ProcessInput(GameEngine* game);
    void Update(GameEngine* game);
    void RenderFrame(GameEngine* game);

    static EntryState* Instance() {
        return &m_EntryState;
    }

protected:
    EntryState() {}

private:
    static EntryState m_EntryState;
    };

#endif // ENTRYSTATE_HPP_INCLUDED
