#ifndef ROOMSBASE_HPP_INCLUDED
#define ROOMSBASE_HPP_INCLUDED

#include <vector>

class Room {
public:
    Room();
    ~Room();
    virtual void Start();
    virtual void Update();
    virtual void End();
};

class RoomManager {
private:
    std::vector<Room> rooms;
public:
    RoomManager();
    ~RoomManager();
};

#endif // ROOMSBASE_HPP_INCLUDED
