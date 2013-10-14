#ifndef LEVELMANAGER_HPP_INCLUDED
#define LEVELMANAGER_HPP_INCLUDED

#include <sstream>
#include <vector>
#include <string>
#include "GameEngine.hpp"

class LevelData;
class IterationData;
class EventData;
class LinkData;

class LevelManager {
private:
    bool StringToInt(std::string &s, int &i);
    std::vector<std::string> Explode(std::string str, char split);
public:
    LevelManager(GameEngine* game);
    ~LevelManager();

    LevelData* levelData;
    IterationData* iterationData;
    EventData* eventData;
    LinkData* linkData;

    void Load(const char* levelName);
    void Update(GameEngine* game);
    void UpdateDisplay(GameEngine* game);
    void UpdateTimeChanged();

    bool timeChangedForwardFlag = false;  // Set to true by IterationData when time changes forward
    bool timeChangedBackwardFlag = false; // Set to true by IterationData when time changes backward
};

#endif // LEVELMANAGER_HPP_INCLUDED
