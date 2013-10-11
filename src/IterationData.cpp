#include <iostream>
#include <sstream>
#include <complex>
#include "IterationData.hpp"

IterationData::IterationData(LevelManager* levelManager) {
    this->levelManager = levelManager;
}

int IterationData::GetTime() {
    return time;
}

std::string IterationData::GetMeltdownTMinus() {
    int t = time - meltdown;
    std::ostringstream os;
    if (t <= 0)
        os << "T-" << std::abs(t);
    else
        os << "T+" << std::abs(t);
    return os.str();
}

std::string IterationData::GetCatastropheTMinus() {
    int t = time - catastrophe;
    std::ostringstream os;
    if (t <= 0)
        os << "T-" << std::abs(t);
    else
        os << "T+" << std::abs(t);
    return os.str();
}

void IterationData::UpdateTimeline(Timeline* timeline) {
    timeline->SetTMinus(GetMeltdownTMinus(), GetCatastropheTMinus());
}

bool IterationData::CanGoForward() {
    return time < catastrophe;
}

void IterationData::GoForward() {
    if (CanGoForward()) {
        time++;
        TimeChanged();
    } else {
        std::cout << "WARNING: Tried to go forwards in time when there is no more time to go forwards to" << std::endl;
    }
}

bool IterationData::CanGoBackward() {
    return time >= 1; // Cannot go backward if we are on time 0
}

void IterationData::GoBackward() {
    if (CanGoBackward()) {
        time--;
        TimeChanged();
    } else {
        std::cout << "WARNING: Tried to go backwards in time when there is no more time to go backwards to" << std::endl;
    }
}

void IterationData::TimeChanged() {
    // Set a flag instead of directly calling levelManager->UpdateTimeChanged()
    // This ensures that the correct order of execution is maintained
    // Since we want it to be determinate in which order events are called
    levelManager->timeChangedFlag = true;
}
