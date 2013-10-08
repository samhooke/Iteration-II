#include "Chronact.hpp"

#include <string>
#include <fstream>
#include "GameEngine.hpp"
#include "TitleState.hpp"
#include "Logger.hpp"
#include "Defs.hpp"

Chronact::Chronact() {}
Chronact::~Chronact() {}

void Chronact::Go() {
    // Load configs
    ReadConfig();

    // Enter main loop
    MainLoop();
}

void Chronact::MainLoop() {

    // Create game engine
    GameEngine* game = new GameEngine();
    game->Init("Iteration II", useShaders);

    // Change game state to the title screen
    game->ChangeState(TitleState::Instance());

    // Actually enter the main loop
    while(game->Running()) {
        game->ProcessInput();
        game->Update();
        game->RenderFrame();
        game->Pause();
    }

    game->CleanUp();
}

void Chronact::ReadConfig() {
    std::cout << "Reading config.txt" << std::endl;

    // Set defaults
    useShaders = true;

    // Attempt to read file
    std::string line;
    std::ifstream myfile(CONFIG_FILENAME);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line == "shaders=no")
                useShaders = false;
        }
        myfile.close();
    } else {
        std::cout << "Cannot open config.txt: reverting to defaults" << std::endl;
    }

    // Print out chosen configuration settings
    if (useShaders)
        std::cout << "Shaders enabled" << std::endl;
    else
        std::cout << "Shaders disabled" << std::endl;
}
