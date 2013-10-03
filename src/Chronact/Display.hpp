#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 35

#define SPRITESHEET_COLS 16
#define SPRITESHEET_ROWS 16
#define SPRITESHEET_SPRITE_W 9
#define SPRITESHEET_SPRITE_H 16

class Display {
private:
    int width;
    int height;
    char tile[DISPLAY_WIDTH][DISPLAY_HEIGHT];
    sf::Texture tileSet;
    sf::Sprite tileSprites[SPRITESHEET_COLS * SPRITESHEET_ROWS];
    void LoadGraphics();
public:
    Display();
    ~Display();

    void SetAll(char c);

    void WriteText(int x, int y, char* text, int maxCharsPerRow = -1, int maxRows = -1, char mask = -1);

    void Render(sf::RenderWindow* window);

    int GetPixelWidth();
    int GetPixelHeight();
};

#endif // DISPLAY_HPP_INCLUDED
