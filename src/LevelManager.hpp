#ifndef LEVELMANAGER_HPP_INCLUDED
#define LEVELMANAGER_HPP_INCLUDED

#include "Display.hpp"
#include "LevelData.hpp"
#include "GameEngine.hpp"

class LevelManager {
private:
    LevelData* levelData;
public:
    LevelManager(GameEngine* game);
    ~LevelManager();

    void Load(const char* levelName);
    void Update(GameEngine* game);
    void UpdateDisplay(Display* display);
};

#endif // LEVELMANAGER_HPP_INCLUDED
