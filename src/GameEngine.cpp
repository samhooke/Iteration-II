#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameEngine.hpp"
#include "GameState.hpp"
#include "Display.hpp"

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

void GameEngine::Init(const char* title, bool useShaders) {

    // Start clock
    gameClock = new sf::Clock();
    gameClock->restart();

    m_running = true;

    // Create graphical interfaces
    display = new Display(useShaders);
    window = new sf::RenderWindow(sf::VideoMode(display->GetPixelWidth(), display->GetPixelHeight(), 32), title, sf::Style::Default); // ::Close to disable resizing

    // Verify the window was created
    if (!window) {
        std::cout << "Could not create window" << std::endl;
        //TODO: Fix this really terrible long pause
        for (int i = 0; i < 100; i++) {Pause();}
        Quit();
    }

    std::cout << "Running Chronact engine" << std::endl;
}

void GameEngine::CleanUp() {
    while (!states.empty()) {
        states.back()->CleanUp();
        states.pop_back();
    }

    std::cout << "Terminating Chronact engine" << std::endl;

    // Clear used resources
    window->close();
    delete display;
    delete window;
}

void GameEngine::ChangeState(GameState* state) {
    if (!states.empty()) {
        states.back()->CleanUp();
        states.pop_back();
    }

    states.push_back(state);
    states.back()->Init(this);
}

void GameEngine::PushState(GameState* state) {
    if (!states.empty()) {
        states.back()->Pause();
    }

    states.push_back(state);
    states.back()->Init(this);
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
