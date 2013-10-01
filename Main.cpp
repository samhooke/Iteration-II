//#include <Window.h>
#include "Engine.h"
#include <iostream>

int main()
{
    Engine* engine = new Engine();

    try
    {
        engine->Go();
    }
    catch (char* e)
    {
        std::cout << e;
    }
}
