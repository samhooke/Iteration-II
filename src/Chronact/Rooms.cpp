#include "Rooms.hpp"

RoomManager::RoomManager() {
    rooms[0] = RoomTitle();
    rooms[1] = RoomBlank();
}

// Base room
Room::Room() {}
Room::~Room() {}
void Room::Start() {}
void Room::Update() {}
void Room::End() {}

// Title screen
void RoomTitle::Start() {}
void RoomTitle::Update() {}
void RoomTitle::End() {}

// Blank room
void RoomBlank::Start() {}
void RoomBlank::Update() {}
void RoomBlank::End() {}

