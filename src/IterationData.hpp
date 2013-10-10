#ifndef ITERATIONMANAGER_HPP_INCLUDED
#define ITERATIONMANAGER_HPP_INCLUDED

#include "Timeline.hpp"
#include <string>

class IterationData {
private:
    int iteration = 0;
    int meltdown = 20;
public:
    void UpdateTimeline(Timeline* timeline);

    int GetCurrentIteration();
    std::string GetTMinus();

    void Forward();
    void Backward();
};

#endif // ITERATIONMANAGER_HPP_INCLUDED
