#ifndef SCENESTATE_HPP_INCLUDED
#define SCENESTATE_HPP_INCLUDED

#include "GameState.hpp"
#include "../GameEngine.hpp"
#include "../LevelManager.hpp"

class SceneState : public GameState {
public:
    void Init(GameEngine* game);
    void CleanUp(GameEngine* game);

    void Pause();
    void Resume();

    void ProcessInput(GameEngine* game);
    void Update(GameEngine* game);
    void RenderFrame(GameEngine* game);

    static SceneState* Instance() {
        return &m_SceneState;
    }
protected:
    SceneState() {}

private:
    static SceneState m_SceneState;

    LevelManager* levelManager;

    std::vector<std::string> text;

    sf::Clock clock;
};

#endif // SCENESTATE_HPP_INCLUDED
