#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Graphics/TextureManager.hpp"
#include "Graphics/Tile.hpp"
#include "Exception.hpp"
#include "Logger.hpp"

class Chronact
{
private:
    // SFML Render Window
    sf::RenderWindow* window;

    // Texture manager
    TextureManager* textureManager;

    bool Init();
    void MainLoop();
    void RenderFrame();
    void ProcessInput();
    void Update();

    //NOTE: Temporary
    void LoadTextures();
    Tile* testTile1;
    Tile* testTile2;
    Tile* testTile3;

public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
