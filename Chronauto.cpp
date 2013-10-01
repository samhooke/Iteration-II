#include "Chronauto.hpp"
#include "Logger.hpp"
#include <SFML\Graphics.hpp>

Chronauto::Chronauto() {

}

Chronauto::~Chronauto() {

}

bool Chronauto::Init() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Iteration II");

    if (!window)
        return false;

    return true;
}

void Chronauto::RenderFrame() {

}

void Chronauto::ProcessInput() {
    sf::Event event;

    // Loop through all window events
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Chronauto::Update() {

}

void Chronauto::MainLoop() {
    // Loop until our window is closed
    while (window->isOpen()) {
        ProcessInput();
        Update();
        RenderFrame();
    }
}

void Chronauto::Go() {
    if (!Init())
        throw "Could not initalize engine!";

    MainLoop();
}
