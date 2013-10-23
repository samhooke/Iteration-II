#include "EventData.hpp"
#include <iostream>
#include "General.hpp"

EventData::EventData() {}
EventData::~EventData() {
    // NOTE: This code seems to cause the game to crash. Specifically, the loop for `tentativeEvents`. I do not think this code is even necessary.
    /*
    // Destroy all events
    for (std::map<int, std::vector<Event::Base*>>::iterator itr = events.begin(), itrEnd = events.end(); itr != itrEnd; ++itr) {
        for (int i = 0; i < (int)(itr->second).size(); ++i) {
            delete (itr->second).at(i);
        }
    }

    for (std::map<int, std::vector<Event::Base*>>::iterator itr = tentativeEvents.begin(), itrEnd = tentativeEvents.end(); itr != itrEnd; ++itr) {
        for (int i = 0; i < (int)(itr->second).size(); ++i) {
            delete (itr->second).at(i);
        }
    }
    */
}

void EventData::AddEvent(Event::Base* event) {
    // Read the time from the event and use that as the key
    if (event->time >= 0)
        events[event->time].push_back(event);
    else
        std::cout << "WARNING: Tried to perform EventData::AddEvent for invalid time: " << event->time << std::endl;
}

void EventData::AddTentativeEvent(Event::Base* tentativeEvent) {
    // Read the time from the event and use that as the key
    if (tentativeEvent->time >= 0)
        tentativeEvents[tentativeEvent->time].push_back(tentativeEvent);
    else
        std::cout << "WARNING: Tried to perform EventData::AddEvent for invalid time: " << tentativeEvent->time << std::endl;
}

void EventData::ExecuteForwardEvents(int time) {
    // Execute tentative events. If they succeed, move them to proper events list
    for (int i = 0; i < (int)tentativeEvents[time].size(); ++i) {
        Event::Result result = tentativeEvents[time].at(i)->ForwardEvent();

        if (result.success) {
            // Tentative event worked
            // Undo what it just did and place it in the proper events list
            tentativeEvents[time].at(i)->BackwardEvent();
            AddEvent(tentativeEvents[time].at(i));

            std::cout << "A tentative event succeeded. It is now a real event!" << std::endl;
        } else {
            std::cout << "A tentative event failed to succeed. This is okay!" << std::endl;
            std::cout << ::Timestamp(time) << "Tentative event with " << tentativeEvents[time].at(i)->debugName << " failed because: " << result.msg << std::endl;
        }
    }

    // Delete all tentative events
    // TODO: Only delete the events that have been processed (those for within tentativeEvents[time])
    tentativeEvents.clear();

    // Execute events in forwards order
    for (int o = EVENT_ORDER_FRONT; o <= EVENT_ORDER_BACK; o++) {
        for (int i = 0; i < (int)events[time].size(); ++i) {
            Event::Base* e = events[time].at(i);
            if (e->order == o) {
                Event::Result result = e->ForwardEvent();

                if (!result.success) {
                    std::cout << ::Timestamp(time) << "Forward paradox with " << events[time].at(i)->debugName << ": " << result.msg << std::endl;
                }
            }
        }
    }
}

void EventData::ExecuteBackwardEvents(int time) {
    // Execute events in backwards order
    for (int o = EVENT_ORDER_BACK; o >= EVENT_ORDER_FRONT; o--) {
        for (int i = (int)events[time].size() - 1; i >= 0 ; --i) {
            Event::Base* e = events[time].at(i);
            if (e->order == o) {
                Event::Result result = e->BackwardEvent();

                if (!result.success) {
                    std::cout << ::Timestamp(time) << "Backward paradox with " << events[time].at(i)->debugName << ": " << result.msg << std::endl;
                }
            }
        }
    }
}
