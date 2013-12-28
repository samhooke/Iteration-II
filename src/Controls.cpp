#include "Controls.hpp"
#include "Defs.hpp"
#include <iostream>

Controls::Controls() {
    // Start clock
    delayClock.restart();
    lastPress.restart();

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
        case InputKey::Enter:   keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_ENTER);       break;
        case InputKey::Restart: keyStateNow[iKey] = sf::Keyboard::isKeyPressed(INPUT_RESTART);     break;
        default:
#ifdef DEBUG_VERBOSE
            std::cout << "WARNING: Trying to update the state of a key that does not exist" << std::endl;
#endif
            break;
        }
        
        // Whenever there is any press, reset the lastPress clock
        if (!keyStatePrev[iKey] && keyStateNow[iKey]) {
            ResetLastPress();
        }
        
        // Whenever there is any release, reset the lastRelease clock
        if (keyStatePrev[iKey] && !keyStateNow[iKey]) {
            ResetLastRelease();
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
    // If it has been sufficient time since a key was pressed,
    // or if a key has recently been released,
    // use the fast delay, else use the slow delay
    if (lastPress.getElapsedTime().asSeconds() > MOVEMENT_DELAY_FAST_THRESHOLD) {
        return (delayClock.getElapsedTime().asSeconds() > MOVEMENT_DELAY_FAST);
    } else {
        return (delayClock.getElapsedTime().asSeconds() > MOVEMENT_DELAY_SLOW);
    }
}

void Controls::ResetKeyDelay() {
    delayClock.restart();
}

void Controls::ResetLastPress() {
    lastPress.restart();
}

void Controls::ResetLastRelease() {
    lastRelease.restart();
}
