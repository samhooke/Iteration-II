#include "ObjectsGeneral.hpp"
#include "Player.hpp"
#include "../LevelData.hpp"
#include "../IterationData.hpp"
#include "../Events.hpp"
#include "../EventData.hpp"

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

    /// PressurePlate
    PressurePlate::PressurePlate(int x, int y, GameEngine* game, LevelManager* levelManager, bool state) : StaticLinkable(x, y, game, levelManager, state) {
        debugName = "PressurePlate";
        UpdateSprite();
    }

    void PressurePlate::UpdateSprite() {
        if (state == STATE_PRESSUREPLATE_UP) {
            displayCharacter = TILE_PRESSUREPLATE_UP;
        } else {
            displayCharacter = TILE_PRESSUREPLATE_DOWN;
        }
    }

    PressurePlate::~PressurePlate() {}

    void PressurePlate::Update() {
        UpdateSprite();
    }

    /// MotionAlarm
    MotionAlarm::MotionAlarm(int x, int y, GameEngine* game, LevelManager* levelManager, bool state) : StaticLinkable(x, y, game, levelManager, state) {
        debugName = "MotionAlarm";
        UpdateSprite();
    }

    void MotionAlarm::UpdateSprite() {
        if (state == STATE_MOTIONALARM_INACTIVE) {
            displayCharacter = TILE_MOTIONALARM;
        } else {
            int t = ((int)(game->gameClock->getElapsedTime().asSeconds() / TIMEMACHINE_SECONDS_PER_DISPLAYCHARACTER));
            if (t % 2 == 0)
                displayCharacter = TILE_MOTIONALARM_ACTIVE_1;
            else
                displayCharacter = TILE_MOTIONALARM_ACTIVE_2;
        }
    }

    MotionAlarm::~MotionAlarm() {}

    void MotionAlarm::Update() {
        UpdateSprite();
    }
}
