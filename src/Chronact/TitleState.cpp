#include "Chronact.hpp"
#include "TitleState.hpp"

TitleState TitleState::m_TitleState;

void TitleState::Init() {}
void TitleState::CleanUp() {}
void TitleState::Pause() {}
void TitleState::Resume() {}
void TitleState::ProcessInput(GameEngine* game) {
    sf::Event event;

    // Loop through all window events
    while (game->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game->window->close();
        }
    }
}

void TitleState::Update(GameEngine* game) {
}

void TitleState::RenderFrame(GameEngine* game) {
    game->window->clear();
    game->display->Render(game->window, game->gameClock);
    game->window->display();
}
