#ifndef LEVELMANAGER_HPP_INCLUDED
#define LEVELMANAGER_HPP_INCLUDED

#include <sstream>
#include <string>
#include "Display.hpp"
#include "LevelData.hpp"
#include "GameEngine.hpp"

class LevelManager {
private:
    LevelData* levelData;
    bool StringToInt(std::string &s, int &i);
public:
    LevelManager(GameEngine* game);
    ~LevelManager();

    void Load(const char* levelName);
    void Update(GameEngine* game);
    void UpdateDisplay(Display* display);
};

#endif // LEVELMANAGER_HPP_INCLUDED
