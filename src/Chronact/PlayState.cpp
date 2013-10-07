#include <iostream>
#include "Chronact.hpp"
#include "PlayState.hpp"
#include "TitleState.hpp"
#include "Tiles.hpp"

PlayState PlayState::m_PlayState;

void PlayState::Init() {
    std::cout << "PlayState::Init()...";
    levelManager = new LevelManager();
    std::cout << "2...";
    levelManager->Load(LEVEL_000);
    std::cout << "3...";
}
void PlayState::CleanUp() {
    delete levelManager;
}
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
        default:
            break;
        }
    }
}

void PlayState::Update(GameEngine* game) {
    levelManager->UpdateDisplay(game->display);
}

void PlayState::RenderFrame(GameEngine* game) {
    game->window->clear();
    game->display->Render(game);
    game->window->display();
}
