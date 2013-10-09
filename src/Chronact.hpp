#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include <string>
#include "Display.hpp"
#include "Exception.hpp"

class Chronact {
private:
    void ReadConfig();
    bool useShaders;
    bool fullscreen;
    sf::Vector2f scale;
    bool DecodeValueYesNo(std::string s);
    float DecodeValueFloat(std::string s);

    void MainLoop();
public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
