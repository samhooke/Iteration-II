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
    int debugRemoveThis[1000];
public:
    LevelManager(GameEngine* game);
    ~LevelManager();

    LevelData* levelData;
    IterationData* iterationData;

    void Load(const char* levelName);
    void Update(GameEngine* game);
    void UpdateDisplay(GameEngine* game);
    void UpdateTimeChanged();

    bool timeChangedFlag = false;   // Set to true by IterationData when time changes
};

#endif // LEVELMANAGER_HPP_INCLUDED
