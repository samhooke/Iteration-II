#ifndef TIMELINE_HPP_INCLUDED
#define TIMELINE_HPP_INCLUDED

#include "GameEngine.hpp"

class Timeline {
private:
    int x = 1;
    int y = 25;
    int width = 78;
    int height = 9;
    int iteration = 0;
public:
    Timeline();
    ~Timeline();

    void UpdateDisplay(GameEngine* game);
};

#endif // TIMELINE_HPP_INCLUDED
