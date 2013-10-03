#include "Display.hpp"

Display::Display(int w, int h) {
    width = w;
    height = h;

    // Populate the tile array with 0s
    for (int i = 0; i < DISPLAY_WIDTH_MAX; i++) {
        for (int j = 0; j < DISPLAY_HEIGHT_MAX; j++) {
            tile[i][j] = '0';
        }
    }

    // Load the texture
    tileSet.loadFromFile("tiles.png");

    testSprite.setTexture(tileSet, true);
}

Display::~Display() {
}

void Display::Render(sf::RenderWindow* window) {
    window->draw(testSprite);
}
