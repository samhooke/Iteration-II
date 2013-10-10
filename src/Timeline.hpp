#ifndef TIMELINE_HPP_INCLUDED
#define TIMELINE_HPP_INCLUDED

#include <string>
#include "GameEngine.hpp"

class Timeline {
private:
    int x = 1;
    int y = 25;
    int width = 78;
    int height = 9;

    std::string tMinus;
public:
    Timeline();
    ~Timeline();

    void SetTMinus(std::string tMinus);

    void UpdateDisplay(GameEngine* game);
};

#endif // TIMELINE_HPP_INCLUDED