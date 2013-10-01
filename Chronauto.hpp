#ifndef CHRONAUTO_HPP_INCLUDED
#define CHRONAUTO_HPP_INCLUDED

#include <SFML\Graphics.hpp>

class Chronauto
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
    Chronauto();
    ~Chronauto();

    // Starts the engine
    void Go();
};

#endif // CHRONAUTO_HPP_INCLUDED
