#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Defs.hpp"

#include "GameEngine.hpp"

class Display {
private:
    int width;
    int height;
    bool shadersEnabled;
    int tile[DISPLAY_WIDTH][DISPLAY_HEIGHT];
    sf::RenderTexture surface;
    sf::RenderTexture effects;
    sf::Texture tileSet;
    sf::Sprite tileSprites[SPRITESHEET_COLS * SPRITESHEET_ROWS];
    void LoadGraphics();
    sf::Shader shader;
    void RenderTilesToSurface();
    void RenderSurfaceToWindow(GameEngine* game);
public:
    Display(bool useShaders);
    ~Display();

    void SetAll(int c);

    void WriteText(int x, int y, char* text, int maxCharsPerRow = -1, int maxRows = -1, int mask[] = NULL);

    void DrawTitle();

    //void Render(sf::RenderWindow* window, sf::Clock* gameClock);
    void Render(GameEngine* game);

    int GetPixelWidth();
    int GetPixelHeight();
};

class WriteMask {
public:
    int mask1;
};

#endif // DISPLAY_HPP_INCLUDED
