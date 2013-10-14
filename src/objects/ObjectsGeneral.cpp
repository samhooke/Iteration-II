#include "ObjectsGeneral.hpp"

namespace GameObject {
    /// Door
    Door::Door(int x, int y, GameEngine* game, LevelManager* levelManager, bool requiresKey, bool state) : StaticLinkable(x, y, game, levelManager, state) {

        debugName = "Door";

        this->requiresKey = requiresKey;
        UpdateSprite();
    }

    void Door::UpdateSprite() {
        if (requiresKey) {
            if (state)
                displayCharacter = TILE_DOORREQUIRESKEY_OPEN;
            else
                displayCharacter = TILE_DOORREQUIRESKEY_SHUT;
        } else {
            if (state)
                displayCharacter = TILE_DOOR_OPEN;
            else
                displayCharacter = TILE_DOOR_SHUT;
        }
    }

    Door::~Door() {}

    void Door::Update() {
        UpdateSprite();
    }

    /// Window
    Window::Window(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        debugName = "Window";
        displayCharacter = TILE_WINDOW;
    }

    Window::~Window() {}

    void Window::Update() {}

    /// Terminal
    Terminal::Terminal(int x, int y, GameEngine* game, LevelManager* levelManager) : Static(x, y, game, levelManager) {
        debugName = "Terminal";
        displayCharacter = TILE_TERMINAL;
    }

    Terminal::~Terminal() {}

    void Terminal::Update() {}

    /// Lever
    Lever::Lever(int x, int y, GameEngine* game, LevelManager* levelManager, bool state) : StaticLinkable(x, y, game, levelManager, state) {
        debugName = "Lever";
        UpdateSprite();
    }

    void Lever::UpdateSprite() {
        if (state == false) {
            displayCharacter = TILE_LEVER_OFF;
        } else {
            displayCharacter = TILE_LEVER_ON;
        }
    }

    Lever::~Lever() {}

    void Lever::Update() {
        UpdateSprite();
    }
}
