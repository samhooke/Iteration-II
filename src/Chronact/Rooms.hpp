#ifndef ROOMS_HPP_INCLUDED
#define ROOMS_HPP_INCLUDED

#define ROOMS_TOTAL 2

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
    Room rooms[ROOMS_TOTAL];
public:
    RoomManager();
    ~RoomManager();
};

class RoomTitle : public Room {
public:
    virtual void Start();
    virtual void Update();
    virtual void End();
};

class RoomBlank : public Room {
public:
    virtual void Start();
    virtual void Update();
    virtual void End();
};

#endif // ROOMS_HPP_INCLUDED
