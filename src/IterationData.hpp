#ifndef ITERATIONMANAGER_HPP_INCLUDED
#define ITERATIONMANAGER_HPP_INCLUDED

#include "LevelManager.hpp"
#include <string>

class IterationData {
private:
    int meltdown = 20;
    int catastrophe = 40;
    LevelManager* levelManager;
public:
    IterationData(LevelManager* levelManager);

    int time = 0;

    int GetTime();
    std::string GetMeltdownTMinus();
    std::string GetCatastropheTMinus();

    bool CanGoForward();
    void GoForward();
    bool CanGoBackward();
    void GoBackward();
    void TimeChangedForward();
    void TimeChangedBackward();
};

#endif // ITERATIONMANAGER_HPP_INCLUDED
