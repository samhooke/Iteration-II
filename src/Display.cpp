#include "Display.hpp"
#include "Tiles.hpp"
#include "Logger.hpp"
#include "PRNG.hpp"

#ifdef OS_UNIX
#include <cmath> // Required for trigonometry under OSX
#endif

Display::Display(bool fullscreen, bool maintainAspectRatio, sf::Vector2f scale, bool useShaders) {
    this->fullscreen = fullscreen;
    this->maintainAspectRatio = maintainAspectRatio;
    this->scale = scale;
    this->useShaders = useShaders;
    LoadGraphics();
    SetAll(TILE_BLANK);
}

void Display::LoadGraphics() {
    // Create rendering surface
    if (!surface.create(GetPixelWidth(), GetPixelHeight())) {
        throw std::runtime_error("Could not create surface.");
    }

    // Load the tileset texture
    tileSet.loadFromFile(SPRITESHEET_FILENAME);

    // Load the logo texture and create sprite
    logo.loadFromFile(LOGO_FILENAME);
    logoSprite.setTexture(logo, true);
    logoSprite.setColor(sf::Color(0, badRand(224, 255), 0));

    // Load each tile sprite
    for (int y = 0; y < SPRITESHEET_ROWS; y++) {
        for (int x = 0; x < SPRITESHEET_COLS; x++) {
            int index = x + y * SPRITESHEET_COLS;
            tileSprites[index].setTexture(tileSet, true);
            tileSprites[index].setTextureRect(sf::IntRect(x * SPRITESHEET_SPRITE_W, y * SPRITESHEET_SPRITE_H, SPRITESHEET_SPRITE_W, SPRITESHEET_SPRITE_H));
            tileSprites[index].setColor(sf::Color(0, badRand(224, 255), 0));
        }
    }

    if (useShaders) {
        // Create surface for shader
        if (!effects.create(GetPixelWidth(), GetPixelHeight())) {
            throw std::runtime_error("Could not create effects.");
        }

        // Load shader
        if (!shader.loadFromFile(SHADER_FRAG_MONITOR3, sf::Shader::Fragment)) {
            throw std::runtime_error("Could not load shader from file: SHADER_FRAG_MONITOR3");
        }
    }
}

void Display::DrawLogo(bool drawLogo, int logoPosX, int logoPosY) {
    this->drawLogo = drawLogo;
    logoSprite.setPosition(logoPosX * SPRITESHEET_SPRITE_W, logoPosY * SPRITESHEET_SPRITE_H);
}

void Display::DrawTitle() {
    int mask[] = {TILE_HASH, TILE_SLASH_FORWARD, TILE_SLASH_BACKWARD};
    // 78 x 12
    char title[] =  "   222                                                                  333   "
                    "  2222 11111 11111 111111 11111      111   11111 11111  111   111   111 3333  "
                    "  22   11111 11111 111111 111111     111   11111 11111 11111  111   111   33  "
                    "  2      1   1 1 1  1   1  1   11   1   1  1 1 1   1   1   1   11    1     3  "
                    "  2      1     1    1 1    1   11   1   1    1     1  1     1  111   1     3  "
                    " 22      1     1    111    11111   1111111   1     1  1     1  1 11  1     33 "
                    " 33      1     1    111    1111    1111111   1     1  1     1  1  11 1     22 "
                    "  3      1     1    1 1    1  11   1     1   1     1  1     1  1   111     2  "
                    "  3      1     1    1   1  1   1   1     1   1     1   1   1   1    11     2  "
                    "  33   11111   1   111111 111 111 111   111  1   11111 11111  111   111   22  "
                    "  3333 11111   1   111111 111 111 111   111  1   11111  111   111   111 2222  "
                    "   333                                                                  222   ";
    WriteText(1, 1, (char*)title, 78, 12, mask);

    WriteText(2, 14, ">.eng_disn -a -F");
    WriteText(2, 15, ">.aut_proc 23");
    WriteText(2, 16, "Connecting:");
    WriteText(2, 17, "timeout (err:-4)");
    WriteText(2, 18, "timeout (err:-4)");
    WriteText(2, 19, "timeout (err:-4)");
    WriteText(2, 20, "timeout (err:7)");
    WriteText(2, 21, "qubytes=47 time=181e7");
    WriteText(2, 22, "Verifying... Success");
    WriteText(2, 23, "Decoding... Success");
    WriteText(2, 25, "Press <return> to analyze data");
}

Display::~Display() {
}

void Display::SetDisplayCharacter(int x, int y, int c) {
    tile[x][y] = c;
}

void Display::SetAll(int c) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            tile[x][y] = c;
        }
    }
}

// Writes text to the display, starting at position x, y.
void Display::WriteText(int x, int y, const char* text, int maxCharsPerRow, int maxRows, int mask[]) {
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

//void Display::Render(sf::RenderWindow* window, sf::Clock* gameClock) {
void Display::Render(GameEngine* game) {
    RenderTilesToSurface();
    if (drawLogo)
        RenderLogoToSurface();
    RenderSurfaceToWindow(game);
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

void Display::RenderLogoToSurface() {
    surface.draw(logoSprite);
}

void Display::RenderSurfaceToWindow(GameEngine* game) {
    // Render the surface to the window
    sf::Sprite surfaceSprite(surface.getTexture());

    // Calculate window size
    sf::Vector2u windowSize = game->window->getSize();

    // Calculate position and scale
    sf::Vector2i pos;
    sf::Vector2f scaleAdjusted; // Amount to scale the surface sprite so that it fits the window and maintains aspect ratio
    sf::Vector2f scaleAdjustedStretch; // Same as scaleAdjusted, but does not maintain ratio

    if (fullscreen) {
        pos.x = windowSize.x/2;
        pos.y = windowSize.y/2;

        scaleAdjustedStretch.x = ((float)windowSize.x / (float)GetPixelWidth());
        scaleAdjustedStretch.y = ((float)windowSize.y / (float)GetPixelHeight());

        if (maintainAspectRatio) {
            // Maintain aspect ratio
            scaleAdjusted.x = 1;
            scaleAdjusted.y = 1;

            // Resize to fit the window
            float scaleResize;
            if (windowSize.x > windowSize.y)
                scaleResize = (float)windowSize.y / (float)GetPixelHeight();
            else
                scaleResize = (float)windowSize.x / (float)GetPixelWidth();

            scaleAdjusted.x *= scaleResize;
            scaleAdjusted.y *= scaleResize;
        }
    } else {
        scaleAdjustedStretch.x = 1;
        scaleAdjustedStretch.y = 1;

        pos.x = GetPixelWidth()/2;
        pos.y = GetPixelHeight()/2;

        if (maintainAspectRatio) {
            // Maintain aspect ratio
            scaleAdjusted.x = (float)GetPixelWidth()/windowSize.x;
            scaleAdjusted.y = (float)GetPixelHeight()/windowSize.y;

            // Resize to fit the window
            float scaleResize;
            if (windowSize.x > windowSize.y)
                scaleResize = (float)windowSize.y / (float)GetPixelHeight();
            else
                scaleResize = (float)windowSize.x / (float)GetPixelWidth();

            scaleAdjusted.x *= scaleResize;
            scaleAdjusted.y *= scaleResize;
        }
    }

    // Place it in the center of the window, even when fullscreen
    surfaceSprite.setOrigin(GetPixelWidth()/2, GetPixelHeight()/2);
    surfaceSprite.setPosition(pos.x, pos.y);

    surfaceSprite.setScale(scaleAdjusted.x, -scaleAdjusted.y); // y must be negative. Not sure why

    game->window->draw(surfaceSprite);

    if (useShaders) {
        // Shader time
        //sf::Vector2i mousePos = sf::Mouse::getPosition(); // Not used

        float t = (game->gameClock->getElapsedTime()).asSeconds();

        // Render the monitor effects on top
        shader.setParameter("resolution", windowSize.x, windowSize.y);
        float mSpeed = 0.05;
        float mDis = 2.0 + std::sin(t * 0.013) * 1.2;
        shader.setParameter("mouse", std::cos(t * mSpeed) * mDis, std::sin(t * mSpeed) * mDis);
        shader.setParameter("alpha", 0.2);
        shader.setParameter("time", t);

        sf::Sprite monitorSprite(effects.getTexture());

        // Place it in the center of the window, even when fullscreen
        monitorSprite.setOrigin(GetPixelWidth()/2, GetPixelHeight()/2);
        monitorSprite.setPosition(pos.x, pos.y);

        monitorSprite.setScale(scaleAdjustedStretch.x, scaleAdjustedStretch.y);

        game->window->draw(monitorSprite, &shader);
    }
}

int Display::GetWidth() {
    return DISPLAY_WIDTH;
}

int Display::GetHeight() {
    return DISPLAY_HEIGHT;
}

int Display::GetPixelWidth() {
    return DISPLAY_WIDTH * SPRITESHEET_SPRITE_W;
}

int Display::GetPixelHeight() {
    return DISPLAY_HEIGHT * SPRITESHEET_SPRITE_H;
}
