#include "Chronact.hpp"

Chronact::Chronact() {
}

Chronact::~Chronact() {
    // Clear used resources
    delete window;
}

bool Chronact::Init() {
    display = new Display();
    window = new sf::RenderWindow(sf::VideoMode(display->GetPixelWidth(), display->GetPixelHeight(), 32), "Iteration II");

    // Verify the window was created
    if (!window)
        return false;

    return true;
}


void Chronact::RenderFrame() {
    window->clear();
    display->Render(window);
    window->display();
}

void Chronact::ProcessInput() {
    sf::Event event;

    // Loop through all window events
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Chronact::Update() {
}

void Chronact::MainLoop() {
    // Loop until our window is closed
    while (window->isOpen()) {
        ProcessInput();
        Update();
        RenderFrame();
    }
}

void Chronact::Go() {

    if (!Init())
        throw EngineInitError();

    LogInfo("Running Chronact engine");
    MainLoop();
}
