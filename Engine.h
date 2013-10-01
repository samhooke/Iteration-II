#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <SFML\Graphics.hpp>

class Engine
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
    Engine();
    ~Engine();

    // Starts the engine
    void Go();
};

#endif // ENGINE_H_INCLUDED
