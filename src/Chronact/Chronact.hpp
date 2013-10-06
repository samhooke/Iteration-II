#ifndef CHRONACT_HPP_INCLUDED
#define CHRONACT_HPP_INCLUDED

#include "Display.hpp"
#include "Exception.hpp"

class Chronact {
private:
    void ReadConfig();
    bool useShaders;

    void MainLoop();
public:
    Chronact();
    ~Chronact();

    // Starts the engine
    void Go();
};

#endif // CHRONACT_HPP_INCLUDED
