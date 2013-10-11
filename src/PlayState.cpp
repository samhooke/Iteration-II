#include <iostream>
#include "Chronact.hpp"
#include "PlayState.hpp"
#include "TitleState.hpp"
#include "Tiles.hpp"
#include "IterationData.hpp"

PlayState PlayState::m_PlayState;

void PlayState::Init(GameEngine* game) {
    timeline = new Timeline();
    levelManager = new LevelManager(game);
    levelManager->Load(LEVEL_000);
}
void PlayState::CleanUp() {
    delete timeline;
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
    //std::cout << "About to call levelManager->UpdateDisplay(game)" << std::endl;
    // Update the tiles in Display
    levelManager->UpdateDisplay(game);
    //std::cout << "About to call levelManager->iterationData->UpdateTimeline(timeline)" << std::endl;
    // Get Iteration to update the timeline's information
    levelManager->iterationData->UpdateTimeline(timeline);
    //std::cout << "About to call timeline->UpdateDisplay(game)" << std::endl;
    // Update the timeline in Display
    timeline->UpdateDisplay(game);
    //std::cout << "About to call game->display->Render(game) and game->window->display()" << std::endl;
    game->display->Render(game);
    game->window->display();
}
