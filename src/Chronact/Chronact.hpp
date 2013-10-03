#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Display.hpp"
#include "Exception.hpp"

class Chronact {
private:
    // SFML Render Window
    sf::RenderWindow* window;

    // Time functions
    sf::Clock clock;
    sf::Time deltaTime; // Use .asSeconds() to convert to float

    // ASCII display
    Display* display;

    bool Init();
    void MainLoop();
    void RenderFrame();
    void ProcessInput();
    void Pause();
    void Update();

    // Room definitions
    enum class Room {Title, Blank};
    enum class RoomEvent {Start, Update, End};
    Room room;

    void RoomStart();
    void RoomUpdate();
    void RoomEnd();

    void RoomTitle(RoomEvent roomEvent);
    void RoomBlank(RoomEvent roomEvent);
public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
