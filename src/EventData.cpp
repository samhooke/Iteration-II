#include "EventData.hpp"

#include <iostream> // Temporary

EventData::EventData() {}
EventData::~EventData() {
    // Destroy all events
    for (std::map<int, std::vector<Event::Base*>>::iterator itr = events.begin(), itrEnd = events.end(); itr != itrEnd; ++itr) {
        for (int i = 0; i < (itr->second).size(); ++i) {
            delete (itr->second).at(i);
        }
    }
}

void EventData::AddEvent(Event::Base* event) {
    // Read the time from the event and use that as the key
    std::cout << "Adding event that occurs at time: " << event->time << std::endl;
    events[event->time].push_back(event);
}

void EventData::ExecuteForwardEvents(int time) {
    // Execute events in forwards order
    for (int i = 0; i < (int)events[time].size(); ++i) {
        Event::Result result = events[time].at(i)->ForwardEvent();

        if (!result.success) {
            std::cout << "[" << time << "] Forward paradox with " << events[time].at(i)->debugName << ": " << result.msg << std::endl;
        }
    }
}

void EventData::ExecuteBackwardEvents(int time) {
    // Execute events in backwards order
    for (int i = (int)events[time].size() - 1; i >= 0 ; --i) {
        Event::Result result = events[time].at(i)->BackwardEvent();

        if (!result.success) {
            std::cout << "[" << time << "] Backward paradox with " << events[time].at(i)->debugName << ": " << result.msg << std::endl;
        }
    }
}
