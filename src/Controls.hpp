#ifndef CONTROLS_HPP_INCLUDED
#define CONTROLS_HPP_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>

enum class InputKey {Up = 0, Down = 1, Left = 2, Right = 3, Action1 = 4, Action2 = 5, __COUNT = 6};

class Controls {
private:
    std::map<InputKey, bool> keyStatePrev;
    std::map<InputKey, bool> keyStateNow;
    sf::Clock delayClock;
public:
    Controls();
    ~Controls();

    void UpdateKeyStates();

    bool GetKeyDown(InputKey key); // True for just the first frame the key is pressed
    bool GetKey(InputKey key);     // True continually while the key is pressed
    bool GetKeyUp(InputKey key);   // True for just the last frame after a key is no longer pressed

    bool GetKeyDelaySufficient();  // Returns true if there has been MOVEMENT_DELAY seconds since DelayReset() was last called
    void ResetKeyDelay();          // Sets the number of seconds since DelayReset() was called to 0
};

#endif // CONTROLS_HPP_INCLUDED
