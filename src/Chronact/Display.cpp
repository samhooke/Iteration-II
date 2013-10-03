#include "Display.hpp"

Display::Display(int w, int h) {
    width = w;
    height = h;

    int x, y;

    // Populate the tile array with 0s
    for (y = 0; y < DISPLAY_HEIGHT_MAX; y++) {
        for (x = 0; x < DISPLAY_WIDTH_MAX; x++) {
            tile[x][y] = '0';
        }
    }

    // Load the texture
    tileSet.loadFromFile("tiles.png");

    // Load each tile sprite
    for (y = 0; y < SPRITESHEET_ROWS; y++) {
        for (x = 0; x < SPRITESHEET_COLS; x++) {
            int index = x + y * SPRITESHEET_COLS;
            tileSprites[index].setTexture(tileSet, true);
            tileSprites[index].setTextureRect(sf::IntRect(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H, SPRITESHEET_SPRITE_W, SPRITESHEET_SPRITE_H));
        }
    }
}

Display::~Display() {
}

void Display::Render(sf::RenderWindow* window) {
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            int index = 2;
            tileSprites[index].setPosition(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H);
            window->draw(tileSprites[index]);
        }
    }
}
