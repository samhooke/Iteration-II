#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#define DISPLAY_WIDTH_MAX 80
#define DISPLAY_HEIGHT_MAX 40

#define SPRITESHEET_COLS 16
#define SPRITESHEET_ROWS 16
#define SPRITESHEET_SPRITE_W 9
#define SPRITESHEET_SPRITE_H 16

class Display {
private:
    int width;
    int height;
    char tile[DISPLAY_WIDTH_MAX][DISPLAY_HEIGHT_MAX];
    sf::Texture tileSet;
    sf::Sprite tileSprites[SPRITESHEET_COLS * SPRITESHEET_ROWS];
public:
    Display(int w, int h);
    ~Display();

    void Render(sf::RenderWindow* window);
};

#endif // DISPLAY_HPP_INCLUDED
