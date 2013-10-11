#include <iostream>
#include <sstream>
#include <complex>
#include "IterationData.hpp"

IterationData::IterationData(LevelManager* levelManager) {
    this->levelManager = levelManager;
}

int IterationData::GetCurrentIteration() {
    return iteration;
}

std::string IterationData::GetTMinus() {
    int t = iteration - meltdown;
    std::ostringstream os;
    if (t <= 0)
        os << "T-" << std::abs(t);
    else
        os << "T+" << std::abs(t);
    return os.str();
}

void IterationData::UpdateTimeline(Timeline* timeline) {
    timeline->SetTMinus(GetTMinus());
}

bool IterationData::CanGoForward() {
    return iteration < catastrophe;
}

void IterationData::GoForward() {
    if (CanGoForward()) {
        iteration++;
        TimeChanged();
    } else {
        std::cout << "WARNING: Tried to go forwards in time when there is no more time to go forwards to" << std::endl;
    }
}

bool IterationData::CanGoBackward() {
    return iteration >= 1; // Cannot go backward if we are on iteration 0
}

void IterationData::GoBackward() {
    if (CanGoBackward()) {
        iteration--;
        TimeChanged();
    } else {
        std::cout << "WARNING: Tried to go backwards in time when there is no more time to go backwards to" << std::endl;
    }
}

void IterationData::TimeChanged() {
    levelManager->UpdateTimeChanged();
}
