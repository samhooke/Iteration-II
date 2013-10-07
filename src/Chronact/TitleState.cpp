#include "Chronact.hpp"
#include "TitleState.hpp"
#include "PlayState.hpp"

TitleState TitleState::m_TitleState;

void TitleState::Init() {}
void TitleState::CleanUp() {}
void TitleState::Pause() {}
void TitleState::Resume() {}
void TitleState::ProcessInput(GameEngine* game) {
    sf::Event event;

    // Loop through all window events
    while (game->window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            game->Quit();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Return)
                game->ChangeState(PlayState::Instance());
            if (event.key.code == sf::Keyboard::Escape)
                game->Quit();
            break;
        default:
            break;
        }
    }
}

void TitleState::Update(GameEngine* game) {
}

void TitleState::RenderFrame(GameEngine* game) {
    game->window->clear();

    game->display->DrawTitle();

    game->display->Render(game);
    game->window->display();
}
