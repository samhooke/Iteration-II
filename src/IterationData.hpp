#ifndef ITERATIONMANAGER_HPP_INCLUDED
#define ITERATIONMANAGER_HPP_INCLUDED

#include "Timeline.hpp"
#include "LevelManager.hpp"
#include <string>

class IterationData {
private:
    int time = 0;
    int meltdown = 20;
    int catastrophe = 40;
    LevelManager* levelManager;
public:
    IterationData(LevelManager* levelManager);

    void UpdateTimeline(Timeline* timeline);

    int GetTime();
    std::string GetMeltdownTMinus();
    std::string GetCatastropheTMinus();

    bool CanGoForward();
    void GoForward();
    bool CanGoBackward();
    void GoBackward();
    void TimeChanged();
};

#endif // ITERATIONMANAGER_HPP_INCLUDED
