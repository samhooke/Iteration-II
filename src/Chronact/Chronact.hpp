#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Display.hpp"
#include "Exception.hpp"

class Chronact {
private:
    // SFML Render Window
    sf::RenderWindow* window;

    // Time functions
    sf::Clock gameClock;
    sf::Clock deltaClock;
    sf::Time deltaTime; // Use .asSeconds() to convert to float

    // ASCII display
    Display* display;

    void ReadConfig();

    bool useShaders;

    bool Init();
    void MainLoop();
    void RenderFrame();
    void ProcessInput();
    void Pause();
    void Update();
public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
