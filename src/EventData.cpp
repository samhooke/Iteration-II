#include "EventData.hpp"

#include <iostream> // Temporary

EventData::EventData() {}
EventData::~EventData() {}

void EventData::AddEvent(Event::Base* event) {
    // Read the time from the event and use that as the key
    std::cout << "Adding event that occurs at time: " << event->time << std::endl;
    events[event->time].push_back(event);
}

void EventData::ExecuteForwardEvents(int time) {
    for (int i = 0; i < (int)events[time].size(); i++) {
        events[time].at(i)->ForwardEvent();
    }
}

void EventData::ExecuteBackwardEvents(int time) {
    for (int i = 0; i < (int)events[time].size(); i++) {
        events[time].at(i)->BackwardEvent();
    }
}
