#ifndef ITERATIONMANAGER_HPP_INCLUDED
#define ITERATIONMANAGER_HPP_INCLUDED

#include "Timeline.hpp"
#include "LevelManager.hpp"
#include <string>

class IterationData {
private:
    int iteration = 0;
    int meltdown = 20;
    LevelManager* levelManager;
public:
    IterationData(LevelManager* levelManager);

    void UpdateTimeline(Timeline* timeline);

    int GetCurrentIteration();
    std::string GetTMinus();

    void Forward();
    void Backward();
    void TimeChanged();
};

#endif // ITERATIONMANAGER_HPP_INCLUDED
