#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "GameEngine.hpp"
#include "GameState.hpp"

#ifdef OS_WINDOWS
#include <windows.h>
void GameEngine::Pause() {
    Sleep(SLEEP_MILLISECONDS);
}
#endif // OS_WINDOWS

#ifdef OS_UNIX
#include <unistd.h>
void GameEngine::Pause() {
    usleep(SLEEP_MILLISECONDS * 1000);
}
#endif // OS_UNIX

void GameEngine::Init(bool useShaders) {
    m_running = true;

    gameClock->restart();

    // Create graphical interfaces
    display = new Display(useShaders);
    window = new sf::RenderWindow(sf::VideoMode(display->GetPixelWidth(), display->GetPixelHeight(), 32), "Iteration II", sf::Style::Default); // ::Close to disable resizing

    // Verify the window was created
    if (!window) {
        printf("Could not create window");
        //TODO: Fix this really terrible long pause
        for (int i = 0; i < 100; i++) {Pause();}
        Quit();
    }

    printf("GameEngine Init");
}

void GameEngine::CleanUp() {
    while (!states.empty()) {
        states.back()->CleanUp();
        states.pop_back();
    }

    printf("GameEngine CleanUp");

    //// Clear used resources
    //delete display;
    //delete window;
}

void GameEngine::ChangeState(GameState* state) {
    if (!states.empty()) {
        states.back()->CleanUp();
        states.pop_back();
    }

    states.push_back(state);
    states.back()->Init();
}

void GameEngine::PushState(GameState* state) {
    if (!states.empty()) {
        states.back()->Pause();
    }

    states.push_back(state);
    states.back()->Init();
}

void GameEngine::PopState(GameState* state) {
    if (!states.empty()) {
        states.back()->CleanUp();
        states.pop_back();
    }

    if (!states.empty()) {
        states.back()->Resume();
    }
}

void GameEngine::ProcessInput() {
    states.back()->ProcessInput(this);
}

void GameEngine::Update() {
    states.back()->Update(this);
}

void GameEngine::RenderFrame() {
    states.back()->RenderFrame(this);
}
