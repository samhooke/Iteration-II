#ifndef LEVELMANAGER_HPP_INCLUDED
#define LEVELMANAGER_HPP_INCLUDED

#include <sstream>
#include <string>
#include "LevelData.hpp"
#include "GameEngine.hpp"
#include "IterationData.hpp"

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
};

#endif // LEVELMANAGER_HPP_INCLUDED
