#ifndef GAMEENGINE_HPP_INCLUDED
#define GAMEENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class Display;

class GameState;

class GameEngine {
public:
    void Init(const char* title, bool useShaders);
    void CleanUp();

    void ChangeState(GameState* state);
    void PushState(GameState* state);
    void PopState(GameState* state);

    void ProcessInput();
    void Update();
    void RenderFrame();

    bool Running() { return m_running; }
    void Quit() { m_running = false; }

    void Pause();

    // SFML Render Window
    sf::RenderWindow* window;

    // Time functions
    sf::Clock* gameClock;
    sf::Time deltaTime; // Use .asSeconds() to convert to float

    // ASCII display
    Display* display;

private:
    std::vector<GameState*> states;

    bool m_running;
    };

#endif // GAMEENGINE_HPP_INCLUDED
