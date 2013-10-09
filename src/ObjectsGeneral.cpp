#include "ObjectsGeneral.hpp"

namespace GameObject {
    // Door
    Door::Door(int x, int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_DOOR;
    }

    Door::~Door() {}

    void Door::Update() {}

    // Window
    Window::Window(int x, int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_WINDOW;
    }

    Window::~Window() {}

    void Window::Update() {}

    // Terminal
    Terminal::Terminal(int x, int y, GameEngine* game, LevelData* levelData) {
        this->x = x;
        this->y = y;
        this->game = game;
        this->levelData = levelData;
        displayCharacter = TILE_TERMINAL;
    }

    Terminal::~Terminal() {}

    void Terminal::Update() {}
}
