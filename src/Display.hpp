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

    void SetDisplayCharacter(unsigned int x, unsigned int y, int c);
    void SetAll(int c);

    void WriteText(int x, int y, const char* text, int maxCharsPerRow = -1, int maxRows = -1, int mask[] = NULL);

    void DrawTitle();

    void Render(GameEngine* game);

    int GetWidth();
    int GetHeight();
    int GetPixelWidth();
    int GetPixelHeight();
};

class WriteMask {
public:
    int mask1;
};

#endif // DISPLAY_HPP_INCLUDED
