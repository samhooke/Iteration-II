#include <iostream>
#include "../Chronact.hpp"
#include "PlayState.hpp"
#include "TitleState.hpp"
#include "../Tiles.hpp"
#include "../IterationData.hpp"

PlayState PlayState::m_PlayState;

void PlayState::Init(GameEngine* game) {
    levelManager = new LevelManager(game);
    if (levelManager->Load(LEVEL_000)) {
        std::cout << "Loaded level successfully" << std::endl;
    } else {
        std::cout << "Failed to load level" << std::endl;
    }
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
    levelManager->Update(game);
}

void PlayState::RenderFrame(GameEngine* game) {
    game->window->clear();

    // Update the tiles in Display
    levelManager->UpdateDisplay(game);

    game->display->Render(game);
    game->window->display();
}
