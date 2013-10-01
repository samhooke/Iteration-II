#include "Chronact.hpp"

Chronact::Chronact() {

}

Chronact::~Chronact() {
    //delete window;
    //delete textureManager;
}

bool Chronact::Init() {
    textureManager = new TextureManager();
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Iteration II");

    if (!window)
        return false;

    LoadTextures();

    return true;
}

void Chronact::LoadTextures() {
    sf::Texture texture;
    texture.loadFromFile("sprites.png");

    textureManager->AddTexture(texture);
    testTile = new Tile(textureManager->GetTexture(0));
}

void Chronact::RenderFrame() {
    window->clear();
    testTile->Draw(0, 0, window);
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
        throw "Could not initalize engine!";

    MainLoop();
}
