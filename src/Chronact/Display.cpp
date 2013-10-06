#include "Display.hpp"

#include "Tiles.hpp"
#include "Logger.hpp"
#include "PRNG.hpp"

Display::Display() {
    LoadGraphics();
    SetAll(TILE_BLANK);
}

void Display::LoadGraphics() {
    // Create rendering surfaces
    if (!surface.create(GetPixelWidth(), GetPixelHeight())) {
        throw std::runtime_error("Could not create surface.");
    }
    if (!effects.create(GetPixelWidth(), GetPixelHeight())) {
        throw std::runtime_error("Could not create effects.");
    }
    if (!effects2.create(GetPixelWidth(), GetPixelHeight())) {
        throw std::runtime_error("Could not create effects2.");
    }

    // Load the texture
    tileSet.loadFromFile(SPRITESHEET_FILENAME);

    // Load each tile sprite
    for (int y = 0; y < SPRITESHEET_ROWS; y++) {
        for (int x = 0; x < SPRITESHEET_COLS; x++) {
            int index = x + y * SPRITESHEET_COLS;
            tileSprites[index].setTexture(tileSet, true);
            tileSprites[index].setTextureRect(sf::IntRect(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H, SPRITESHEET_SPRITE_W, SPRITESHEET_SPRITE_H));
            //tileSprites[index].setColor(sf::Color(0, 127, 0));
            tileSprites[index].setColor(sf::Color(0, badRand(0, 255), 0));
        }
    }

    // Load shader
    if (!shader.loadFromFile(SHADER_FRAG_REAKTOR2, sf::Shader::Fragment)) {
        throw std::runtime_error("Could not load shader from file: SHADER_FRAG_REAKTOR2");
    }

    if (!shader2.loadFromFile(SHADER_FRAG_FRACTAL2, sf::Shader::Fragment)) {
        throw std::runtime_error("Could not load shader from file: SHADER_FRAG_FRACTAL2");
    }

    //float blurRadius = 0.003f;
    //shader.setParameter("blur_radius", blurRadius);
    //shader.setParameter("wave_phase", 0);
    //shader.setParameter("wave_amplitude", 40, 40);
    //shader.setParameter("mouse", 1, 100);
    //shader.setParameter("time", 100.0f);
    //shader.setParameter("surfacePosition", 0, 0);
    //shader.setParameter("resolution", GetPixelWidth(), GetPixelHeight());
}

void Display::DrawBackground() {
    char background[DISPLAY_WIDTH * DISPLAY_HEIGHT];
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        if (badRand(0, 300) == 0)
            background[i] = TILE_0 + badRand(1, 9);
        else
            background[i] = ' ';
    }
    int mask[] = {TILE_BLANK, TILE_FULLSTOP, TILE_DIAMOND, TILE_CARET, TILE_COMMA, TILE_DOT_SOLID, TILE_DOT_OUTLINE, TILE_APOSTROPHE, TILE_ASTERISK};
    WriteText(0, 0, background, DISPLAY_WIDTH, DISPLAY_HEIGHT, mask);
}

void Display::DrawTitle() {
    int mask[] = {TILE_FADE_DARK, TILE_FADE_MIDDLE, TILE_FADE_LIGHT};
    // 80 x 12
    char title[] =  "   111                                                                    111   "
                    "  1111 11111 11111 111111 11111       111    11111 11111  111   111   111 1111  "
                    "  11   11111 11111 111111 111111      111    11111 11111 11111  111   111   11  "
                    "  1      1   1 1 1  1   1  1   11    1   1   1 1 1   1   1   1   11    1     1  "
                    "  1      1     1    1 1    1   11    1   1     1     1  1     1  111   1     1  "
                    " 11      1     1    111    11111    1111111    1     1  1     1  1 11  1     11 "
                    " 11      1     1    111    1111     1111111    1     1  1     1  1  11 1     11 "
                    "  1      1     1    1 1    1  11    1     1    1     1  1     1  1   111     1  "
                    "  1      1     1    1   1  1   1    1     1    1     1   1   1   1    11     1  "
                    "  11   11111   1   111111 111 111  111   111   1   11111 11111  111   111   11  "
                    "  1111 11111   1   111111 111 111  111   111   1   11111  111   111   111 1111  "
                    "   111                                                                    111   ";
    /*
    //72 x 10
    char title[] =  "1111111 1111111 1111111 111111   111111  1111111 1111111  11111  11   11"
                    "1111111 1111111 1111111 1111111 11111111 1111111 1111111 1111111 11   11"
                    "  111     111   111     11   11 11    11   111     111   11   11 111  11"
                    "  111     111   111     11   11 11    11   111     111   11   11 1111 11"
                    "  111     111   1111111 111111  11111111   111     111   11   11 1111111"
                    "  111     111   1111111 111111  11111111   111     111   11   11 1111111"
                    "  111     111   111     11   11 111  111   111     111   11   11 11 1111"
                    "  111     111   111     11   11 11    11   111     111   11   11 11  111"
                    "1111111   111   1111111 11   11 11    11   111   1111111 1111111 11   11"
                    "1111111   111   1111111 11   11 11    11   111   1111111  11111  11   11";
    */
    bool darkLine = false;
    for (int i = 0;; i++) {
        if (title[i] == '\0')
            break;
        /*
        if (i % 80 == 0) {
            darkLine = (badRand(0, 2) == 0);
        }
        if (darkLine) {
            if (title[i] == '1')
                title[i] = '2';
        }
        */
        /*
        if (title[i] == '1') {
            if (badRand(0, 3) == 0) {
                title[i] = '2';
            }
        }
        */
    }

    WriteText(0, 1, (char*)title, 80, 12, mask);

    //WriteText(4, 4 + 10 + 2, "Awaiting command...");
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

void Display::Render(sf::RenderWindow* window, sf::Clock* gameClock) {
    RenderTilesToSurface();
    RenderSurfaceToWindow(window, gameClock);
}

void Display::RenderTilesToSurface() {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            int index = tile[x][y];
            tileSprites[index].setPosition(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H);
            surface.draw(tileSprites[index]);
        }
    }
}

void Display::RenderSurfaceToWindow(sf::RenderWindow* window, sf::Clock* gameClock) {
    // Render the surface to the window
    sf::Sprite surfaceSprite(surface.getTexture());
    surfaceSprite.setOrigin(GetPixelWidth()/2, GetPixelHeight()/2);
    surfaceSprite.setPosition(GetPixelWidth()/2, GetPixelHeight()/2);
    surfaceSprite.setScale(1.0f, -1.0f);
    window->draw(surfaceSprite);

    // Shader time
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    sf::Vector2u windowSize = window->getSize();
    float t = (gameClock->getElapsedTime()).asSeconds();

    // Render the monitor effects on top
    //shader2.setParameter("time", t);
    //shader2.setParameter("alpha", 0.4f);
    shader2.setParameter("resolution", windowSize.x, windowSize.y);
    shader2.setParameter("mouse", mousePos.x/(float)GetPixelWidth(), mousePos.y/(float)GetPixelHeight());
    shader2.setParameter("alpha", 0.3);

    sf::Sprite monitorSprite(effects2.getTexture());
    window->draw(monitorSprite, &shader2);

    // Render the title effects on top of that
    shader.setParameter("time", t);
    //shader.setParameter("mouse", mousePos.x/(float)GetPixelWidth(), mousePos.y/(float)GetPixelHeight() * 4);

    shader.setParameter("resolution", windowSize.x, windowSize.y);
    //printf("%d\n", windowSize.y);
    //shader.setParameter("resolution", GetPixelWidth(), GetPixelHeight());
    //shader.setParameter("alpha", 0.8f);

    sf::Sprite effectsSprite(effects.getTexture());
    //window->draw(effectsSprite, &shader);
}

int Display::GetPixelWidth() {
    return DISPLAY_WIDTH * SPRITESHEET_SPRITE_W;
}

int Display::GetPixelHeight() {
    return DISPLAY_HEIGHT * SPRITESHEET_SPRITE_H;
}
