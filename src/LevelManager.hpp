#ifndef LEVELMANAGER_HPP_INCLUDED
#define LEVELMANAGER_HPP_INCLUDED

#include <sstream>
#include <string>
#include "GameEngine.hpp"

class LevelData;
class IterationData;

class LevelManager {
private:
    bool StringToInt(std::string &s, int &i);
public:
    LevelManager(GameEngine* game);
    ~LevelManager();

    LevelData* levelData;
    IterationData* iterationData;

    void Load(const char* levelName);
    void Update(GameEngine* game);
    void UpdateDisplay(GameEngine* game);
    void UpdateTimeChanged();
};

#endif // LEVELMANAGER_HPP_INCLUDED
