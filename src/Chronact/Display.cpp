#include "Display.hpp"

#include "Tiles.hpp"

Display::Display(int w, int h) {
    width = w;
    height = h;

    int x, y;

    // Populate the tile array with 0s
    for (y = 0; y < DISPLAY_HEIGHT_MAX; y++) {
        for (x = 0; x < DISPLAY_WIDTH_MAX; x++) {
            tile[x][y] = TILE_BLANK;
        }
    }

    tile[1][1] = TILE_H_UPPER;
    tile[2][1] = TILE_E_LOWER;
    tile[3][1] = TILE_L_LOWER;
    tile[4][1] = TILE_L_LOWER;
    tile[5][1] = TILE_O_LOWER;
    tile[6][1] = TILE_COMMA;

    tile[8][1] = TILE_W_LOWER;
    tile[9][1] = TILE_O_LOWER;
    tile[10][1] = TILE_R_LOWER;
    tile[11][1] = TILE_L_LOWER;
    tile[12][1] = TILE_D_LOWER;
    tile[13][1] = TILE_EXCLAMATION_DOUBLE;

    WriteText(1, 2, "Hello, world!");

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

void Display::WriteText(int x, int y, char* text) {
    int i;
    for (i = 0;; i++) {
        if (text[i] == '\0')
            break;
        tile[x + i][y] = (int)text[i];
    }
}

void Display::Render(sf::RenderWindow* window) {
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            int index = tile[x][y];
            tileSprites[index].setPosition(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H);
            window->draw(tileSprites[index]);
        }
    }
}
