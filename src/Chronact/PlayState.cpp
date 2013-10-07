#include "Chronact.hpp"
#include "PlayState.hpp"
#include "TitleState.hpp"
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
        switch (event.type) {
        case sf::Event::Closed:
            game->Quit();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->ChangeState(TitleState::Instance());
            break;
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
