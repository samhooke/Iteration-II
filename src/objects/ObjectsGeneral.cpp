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

    void PressurePlate::UpdateTimeChanged() {
        // Reset the state everytime time changes
        state = STATE_PRESSUREPLATE_UP;

        // Check whether something is pushing us down
        int index = GetObjectIndexAtPosWithTag(x, y, TAG_PLAYER);
        if (index >= 0) {
            // TODO: Simply setting the state based upon whether there is an obejct on top might be slightly hacky
            // The proper method would be to use Events (see the commented out code below)
            // The reason the code is commented it is because it does not work
            // The reason the code does not work is because of the execution order in LevelManager::Update()
            // eventData->ExecuteForwardEvents() is called before UpdateTimeChanged() <= this function
            // This means that if we create an event in the UpdateTimeChanged function, it will not be executed until
            // the end of this time frame(!)
            // A potential fix might be to add an UpdateTimeChangedEarly() event which is called BEFORE eventData->ExecuteForwardEvents()
            // but that makes the main loop even more complicated, especially when considering it must be in the right order forward and backwards
            state = STATE_PRESSUREPLATE_DOWN;

            /*
            Player* player = (Player*)levelManager->levelData->GetObjectPointer(index);
            int time = levelManager->iterationData->GetTime() - 1;

            Event::LinkableStateChange* eventPlatePress = new Event::LinkableStateChange(time, (GameObject::StaticLinkable*)this, player, x, y, STATE_PRESSUREPLATE_UP);
            levelManager->eventData->AddEvent(eventPlatePress);

            Event::LinkableStateChange* eventPlateRelease = new Event::LinkableStateChange(time + 1, (GameObject::StaticLinkable*)this, player, x, y, STATE_PRESSUREPLATE_DOWN);
            levelManager->eventData->AddEvent(eventPlateRelease);

            eventPlatePress->ForwardEvent();
            */
        }

    }

}
