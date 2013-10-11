#include "ObjectsGeneral.hpp"

namespace GameObject {
    // Door
    Door::Door(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        displayCharacter = TILE_DOOR;
        debugName = "Door";
    }

    Door::~Door() {}

    void Door::Update() {}

    // Window
    Window::Window(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        displayCharacter = TILE_WINDOW;
        debugName = "Window";
    }

    Window::~Window() {}

    void Window::Update() {}

    // Terminal
    Terminal::Terminal(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        displayCharacter = TILE_TERMINAL;
        debugName = "Terminal";
    }

    Terminal::~Terminal() {}

    void Terminal::Update() {}
}
