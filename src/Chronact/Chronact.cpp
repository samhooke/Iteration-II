#include "Chronact.hpp"

Chronact::Chronact() {
}

Chronact::~Chronact() {
    // Clear used resources
    delete window;
    delete textureManager;
}

bool Chronact::Init() {
    // Create managers
    textureManager = new TextureManager();
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Iteration II");

    // Verify the window was created
    if (!window)
        return false;

    LoadTextures();

    return true;
}

void Chronact::LoadTextures() {
    sf::Texture texture;
    texture.loadFromFile("sprites.png");

    textureManager->Add(texture);
    testTile1 = new Tile(textureManager->Get(0));
    testTile2 = new Tile(textureManager->Get(0));
    testTile3 = new Tile(textureManager->Get(0));
}

void Chronact::RenderFrame() {
    window->clear();
    testTile1->Draw(0, 0, window);
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

    //LogInfo("Running Chronact engine");
    MainLoop();
}
