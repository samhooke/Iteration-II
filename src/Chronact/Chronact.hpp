#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include <SFML\Graphics.hpp>
#include "Logger\Logger.hpp"

class Chronact
{
private:
    // SFML Render Window
    sf::RenderWindow* window;

    // Initalize the engine
    bool Init();

    // Main game loop
    void MainLoop();

    // Render one frame
    void RenderFrame();

    // Process user input
    void ProcessInput();

    // Update all engine internals
    void Update();

public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
