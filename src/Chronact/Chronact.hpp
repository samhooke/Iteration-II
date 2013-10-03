#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "Exception.hpp"
#include "Logger.hpp"

class Chronact
{
private:
    // SFML Render Window
    sf::RenderWindow* window;

    // Current level
    Level* level;

    bool Init();
    void MainLoop();
    void RenderFrame();
    void ProcessInput();
    void Update();

public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
