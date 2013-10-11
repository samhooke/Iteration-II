#ifndef CONTROLS_HPP_INCLUDED
#define CONTROLS_HPP_INCLUDED

#include <map>

enum class InputKey {Up = 0, Down = 1, Left = 2, Right = 3, Action1 = 4, Action2 = 5, __COUNT = 6};

class Controls {
private:
    std::map<InputKey, bool> keyStatePrev;
    std::map<InputKey, bool> keyStateNow;
public:
    Controls();
    ~Controls();

    void UpdateKeyStates();

    bool GetKeyDown(InputKey key);
    bool GetKey(InputKey key);
    bool GetKeyUp(InputKey key);
};

#endif // CONTROLS_HPP_INCLUDED
