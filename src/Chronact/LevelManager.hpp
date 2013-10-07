#ifndef LEVELMANAGER_HPP_INCLUDED
#define LEVELMANAGER_HPP_INCLUDED

#include "Display.hpp"
#include "LevelData.hpp"

class LevelManager {
private:
    LevelData levelData;
public:
    LevelManager();
    ~LevelManager();

    void Load(const char* levelName);
    void UpdateDisplay(Display* display);
};

#endif // LEVELMANAGER_HPP_INCLUDED
