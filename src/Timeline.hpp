#ifndef TIMELINE_HPP_INCLUDED
#define TIMELINE_HPP_INCLUDED

#include <string>
#include "GameEngine.hpp"
#include "LevelManager.hpp"

class Timeline {
public:
    Timeline();
    ~Timeline();

    void UpdateDisplay(GameEngine* game, LevelManager* levelManager);
};

#endif // TIMELINE_HPP_INCLUDED
