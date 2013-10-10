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

void IterationData::Forward() {
    iteration++;
    TimeChanged();
}

void IterationData::Backward() {
    iteration--;
    TimeChanged();
}

void IterationData::TimeChanged() {
    levelManager->UpdateTimeChanged();
}
