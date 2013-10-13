#include "ObjectsGeneral.hpp"

namespace GameObject {
    // Door
    Door::Door(int x, int y, GameEngine* game, LevelManager* levelManager, bool requiresKey) : Static(x, y, game, levelManager) {

        debugName = "Door";

        this->requiresKey = requiresKey;
        UpdateSprite();
    }

    void Door::UpdateSprite() {
        if (requiresKey) {
            if (open)
                displayCharacter = TILE_DOORREQUIRESKEY_OPEN;
            else
                displayCharacter = TILE_DOORREQUIRESKEY_SHUT;
        } else {
            if (open)
                displayCharacter = TILE_DOOR_OPEN;
            else
                displayCharacter = TILE_DOOR_SHUT;
        }
    }

    Door::~Door() {}

    void Door::Update() {
        UpdateSprite();
    }

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
