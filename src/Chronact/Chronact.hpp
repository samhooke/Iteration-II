#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include <SFML\Graphics.hpp>
#include "Logger\Logger.hpp"
#include "Graphics\TextureManager.hpp"
#include "Graphics\Tile.hpp"

class Chronact
{
private:
    // SFML Render Window
    sf::RenderWindow* window;

    // Texture manager
    TextureManager* textureManager;

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

    //NOTE: Temporary
    void LoadTextures();
    Tile* testTile;

public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
