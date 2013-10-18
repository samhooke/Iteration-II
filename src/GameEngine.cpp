#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "GameEngine.hpp"
#include "states/GameState.hpp"
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

void GameEngine::Init(const char* title, bool fullscreen, bool maintainAspectRatio, sf::Vector2f scale, bool useShaders) {

    // Start clock
    gameClock = new sf::Clock();
    gameClock->restart();

    m_running = true;

    // Create graphical interfaces
    display = new Display(fullscreen, maintainAspectRatio, scale, useShaders);
    if (fullscreen)
        window = new sf::RenderWindow(sf::VideoMode(display->GetPixelWidth(), display->GetPixelHeight(), 32), title, sf::Style::Fullscreen);
    else
        window = new sf::RenderWindow(sf::VideoMode(display->GetPixelWidth(), display->GetPixelHeight(), 32), title, sf::Style::Default);

    // Verify the window was created
    if (!window) {
        std::cout << "Could not create window" << std::endl;
        //TODO: Fix this really terrible long pause
        for (int i = 0; i < 100; i++) {Pause();}
        Quit();
    }

    // Create object to handle controls
    controls = new Controls();

    // Create object to handle content
    content = new Content(this);
    content->LoadOutline();

    std::cout << "Running..." << std::endl;
}

void GameEngine::CleanUp() {
    while (!states.empty()) {
        states.back()->CleanUp(this);
        states.pop_back();
    }

    std::cout << "Terminated!" << std::endl;

    // Clear used resources
    window->close();
    delete controls;
    delete content;
    delete display;
    delete window;
}

void GameEngine::ChangeState(GameState* state) {
    if (!states.empty()) {
        states.back()->CleanUp(this);
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
        states.back()->CleanUp(this);
        states.pop_back();
    }

    if (!states.empty()) {
        states.back()->Resume();
    }
}

void GameEngine::ProcessInput() {
    controls->UpdateKeyStates();
    states.back()->ProcessInput(this);
}

void GameEngine::Update() {
    states.back()->Update(this);
}

void GameEngine::RenderFrame() {
    states.back()->RenderFrame(this);
}
