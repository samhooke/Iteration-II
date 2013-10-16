#ifndef EVENTDATA_HPP_INCLUDED
#define EVENTDATA_HPP_INCLUDED

#include "EventBase.hpp"
#include <vector>
#include <map>

class EventData {
public:
    EventData();
    ~EventData();

    // Each event is stored in a vector of type Event::Base*
    // Each vector is a value in a key/value map, where the key is the time
    std::map<int, std::vector<Event::Base*>> events;
    std::map<int, std::vector<Event::Base*>> tentativeEvents;

    // Add an event to occur at a specific time
    void AddEvent(Event::Base* event);
    void AddTentativeEvent(Event::Base* tentativeEvent);

    // Execute all events that occur at a specific time
    void ExecuteForwardEvents(int time);
    void ExecuteBackwardEvents(int time);
};

#endif // EVENTDATA_HPP_INCLUDED
