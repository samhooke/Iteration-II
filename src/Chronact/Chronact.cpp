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
    printf("Reading config.txt file\n");
    ReadConfig();

    // Enter main loop
    printf("Running Chronact engine\n");
    MainLoop();
}

void Chronact::MainLoop() {
    // Create game engine
    GameEngine game;
    game.Init("Iteration II", useShaders);

    // Change game state to the title screen
    game.ChangeState(TitleState::Instance());

    // Actually enter the main loop
    while(game.Running()) {
        game.ProcessInput();
        game.Update();
        game.RenderFrame();
    }

    game.CleanUp();
}

void Chronact::ReadConfig() {

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
        printf("Cannot open config.txt: reverting to defaults\n");
    }

    // Print out chosen configuration settings
    if (useShaders)
        printf("Shaders enabled\n");
    else
        printf("Shaders disabled\n");
}
