#include "EntryState.hpp"
#include "../Display.hpp"
#include "../Tiles.hpp"

EntryState EntryState::m_EntryState;

void EntryState::Init(GameEngine* game) {
}

void EntryState::CleanUp(GameEngine* game) {}
void EntryState::Pause() {}
void EntryState::Resume() {}
void EntryState::ProcessInput(GameEngine* game) {}

void EntryState::Update(GameEngine* game) {
    // Load the first content
    game->content->Load();
}

void EntryState::RenderFrame(GameEngine* game) {
    game->window->clear();

    game->display->SetAll(TILE_BLANK);

    game->display->Render(game);
    game->window->display();
}
