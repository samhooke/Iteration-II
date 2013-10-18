#include "SceneState.hpp"

SceneState SceneState::m_SceneState;

void SceneState::Init(GameEngine* game) {}
void SceneState::CleanUp(GameEngine* game) {}

void SceneState::Pause() {}
void SceneState::Resume() {}

void SceneState::ProcessInput(GameEngine* game) {}
void SceneState::Update(GameEngine* game) {}
void SceneState::RenderFrame(GameEngine* game) {}
