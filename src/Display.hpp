#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Defs.hpp"

#include "GameEngine.hpp"

class Display {
private:
    int width;
    int height;
    sf::Vector2f scale;
    bool useShaders;
    bool fullscreen;
    bool maintainAspectRatio;
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
    Display(bool fullscreen, bool maintainAspectRatio, sf::Vector2f scale, bool useShaders);
    ~Display();

    void SetDisplayCharacter(int x, int y, int c);
    void SetAll(int c);

    void WriteText(int x, int y, const char* text, int maxCharsPerRow = -1, int maxRows = -1, int mask[] = NULL);

    void DrawTitle();

    void Render(GameEngine* game);

    // Numbers of rows and columns for characters (e.g. 80x35)
    int GetWidth();
    int GetHeight();

    // The size being rendered at (i.e. num rows * tile width X num cols * tile height)
    int GetPixelWidth();
    int GetPixelHeight();
};

class WriteMask {
public:
    int mask1;
};

#endif // DISPLAY_HPP_INCLUDED
