#include "Chronact.hpp"
#include "PlayState.hpp"
#include "Tiles.hpp"

PlayState PlayState::m_PlayState;

void PlayState::Init() {}
void PlayState::CleanUp() {}
void PlayState::Pause() {}
void PlayState::Resume() {}
void PlayState::ProcessInput(GameEngine* game) {
    sf::Event event;

    // Loop through all window events
    while (game->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game->Quit();
        }
    }
}

void PlayState::Update(GameEngine* game) {
}

void PlayState::RenderFrame(GameEngine* game) {
    game->window->clear();

    game->display->SetAll(TILE_BLANK);
    //game->display->DrawTitle();

    game->display->Render(game);
    game->window->display();
}
