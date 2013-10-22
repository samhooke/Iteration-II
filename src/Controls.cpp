#include "Controls.hpp"
#include "Defs.hpp"
#include <iostream>

Controls::Controls() {
    // Start clock
    delayClock.restart();

    // Set all key states to false
    for (int i = 0; i < (int)InputKey::__COUNT; i++) {
        keyStatePrev[(InputKey)i] = false;
        keyStateNow[(InputKey)i] = false;
    }
}

Controls::~Controls() {

}

void Controls::UpdateKeyStates() {
    for (int i = 0; i < (int)InputKey::__COUNT; i++) {
        InputKey iKey = (InputKey)i;
        keyStatePrev[iKey] = keyStateNow[iKey];
        switch (iKey) {
        case InputKey::Up:      keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_UP);          break;
        case InputKey::Down:    keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_DOWN);        break;
        case InputKey::Left:    keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_LEFT);        break;
        case InputKey::Right:   keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_RIGHT);       break;
        case InputKey::Action1: keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_ACTION_1);    break;
        case InputKey::Action2: keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_ACTION_2);    break;
        case InputKey::Enter:   keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_ENTER);    break;
        default:
#ifdef DEBUG_VERBOSE
            std::cout << "WARNING: Trying to update the state of a key that does not exist" << std::endl;
#endif
            break;
        }
    }
}

bool Controls::GetKeyDown(InputKey key) {
    return (!keyStatePrev[key] && keyStateNow[key]);
}

bool Controls::GetKey(InputKey key) {
    return (keyStateNow[key]);
}

bool Controls::GetKeyUp(InputKey key) {
    return (keyStatePrev[key] && !keyStateNow[key]);
}

bool Controls::GetKeyDelaySufficient() {
    return (delayClock.getElapsedTime().asSeconds() > MOVEMENT_DELAY);
}

void Controls::ResetKeyDelay() {
    delayClock.restart();
}
