#include "Display.hpp"

#include "Tiles.hpp"
#include "Logger.hpp"

Display::Display(int w, int h) {

    width = w;
    height = h;

    SetAll(TILE_BLANK);

    WriteText(1, 0, "Hello, world!", 4, 4);

    // Load the texture
    tileSet.loadFromFile("tiles.png");

    // Load each tile sprite
    for (int y = 0; y < SPRITESHEET_ROWS; y++) {
        for (int x = 0; x < SPRITESHEET_COLS; x++) {
            int index = x + y * SPRITESHEET_COLS;
            tileSprites[index].setTexture(tileSet, true);
            tileSprites[index].setTextureRect(sf::IntRect(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H, SPRITESHEET_SPRITE_W, SPRITESHEET_SPRITE_H));
        }
    }
}

Display::~Display() {
}

void Display::SetAll(char c) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tile[x][y] = c;
        }
    }
}

// Writes text to the display, starting at position x, y.
void Display::WriteText(int x, int y, char* text, int maxCharsPerRow, int maxRows) {
    int charsThisLine = 0, rowsDropped = 0;
    for (int i = 0;; i++) {

        // Break if end of string
        if (text[i] == '\0')
            break;

        // Error if outside display limits
        if (i > DISPLAY_HEIGHT_MAX * DISPLAY_WIDTH_MAX)
            throw std::overflow_error("Tried to WriteText outside of the tile range.");

        // If maxCharsPerRow is 1 or greater, limit the chars per row
        // When the limit is exceeded, the text drops down a row
        if (maxCharsPerRow > 0 && charsThisLine >= maxCharsPerRow) {
            rowsDropped++;
            charsThisLine = 0;

            // If maxRows is 1 or greater, limit the rows
            // When the limit is exceeded, the text is truncated
            if (maxRows > 0 && rowsDropped >= maxRows)
                break;
        }

        // Update the display
        tile[x + charsThisLine][y + rowsDropped] = (int)text[i];
        charsThisLine++;
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
