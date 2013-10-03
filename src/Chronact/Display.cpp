#include "Display.hpp"

#include "Tiles.hpp"
#include "Logger.hpp"

Display::Display() {
    LoadGraphics();
    SetAll(TILE_BLANK);
    WriteText(1, 0, "Hello, world!", 4, 4);
    int mask[] = {TILE_FADE_DARK, TILE_FADE_MIDDLE, TILE_FADE_LIGHT};
    WriteText(0, 4, "12112 11211 12111 11112"
                    "  2   2     2       2  "
                    "  2   12112 32123   3  "
                    "  3   2         2   2  "
                    "  3   32323 32333   3  "
                    ,23, 5, mask);
}

void Display::LoadGraphics() {
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

void Display::SetAll(int c) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            tile[x][y] = c;
        }
    }
}

// Writes text to the display, starting at position x, y.
void Display::WriteText(int x, int y, char* text, int maxCharsPerRow, int maxRows, int mask[]) {
    int charsThisLine = 0, rowsDropped = 0;
    for (int i = 0;; i++) {

        // Break if end of string
        if (text[i] == '\0')
            break;

        // Error if outside display limits
        if (i > DISPLAY_HEIGHT * DISPLAY_WIDTH)
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
        if (!mask) {
            // If no mask is supplied, simply write the matching character from `text`
            tile[x + charsThisLine][y + rowsDropped] = (int)text[i];
        } else {
            // If a mask is supplied, whenever there is a `1`, write the mask character
            if (text[i] >= TILE_1 && text[1] <= TILE_9)
                tile[x + charsThisLine][y + rowsDropped] = mask[text[i] - TILE_1];
        }
        charsThisLine++;
    }
}

void Display::Render(sf::RenderWindow* window) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            int index = tile[x][y];
            tileSprites[index].setPosition(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H);
            window->draw(tileSprites[index]);
        }
    }
}

int Display::GetPixelWidth() {
    return DISPLAY_WIDTH * SPRITESHEET_SPRITE_W;
}

int Display::GetPixelHeight() {
    return DISPLAY_HEIGHT * SPRITESHEET_SPRITE_H;
}
