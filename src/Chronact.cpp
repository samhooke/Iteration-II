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
    game->Init("Iteration II", fullscreen, scale, useShaders);

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
    fullscreen = false;
    scale.x = 1.0f;
    scale.y = 1.0f;

    // Attempt to read file
    std::string line;
    std::ifstream myfile(CONFIG_FILENAME);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            // Work out which setting this is for
            int equalsAt = -1;
            for (int i = 0; i < (int)line.length(); i++) {
                if (line[i] == '=') {
                    equalsAt = i;
                    break;
                }
            }

            // There was an equals so read the setting name and value
            if (equalsAt > 0) {
                std::string settingName = line.substr(0, equalsAt);
                std::string settingValue = line.substr(equalsAt + 1);

                if (settingName == "shaders")               useShaders = DecodeValueYesNo(settingValue);
                if (settingName == "fullscreen")            fullscreen = DecodeValueYesNo(settingValue);
                if (settingName == "fullscreen_scale_x")    scale.x = DecodeValueFloat(settingValue);
                if (settingName == "fullscreen_scale_y")    scale.y = DecodeValueFloat(settingValue);
            }
        }
        myfile.close();
    } else {
        std::cout << "Cannot open config.txt: reverting to defaults" << std::endl;
    }

    // Force scale to 1:1 if not fullscreen because scaling does not resize the window
    if (!fullscreen) {
        scale.x = 1.0f;
        scale.y = 1.0f;
    }

    // Print out chosen configuration settings
    std::cout << std::endl << "Launching with the following settings:" << std::endl;
    std::cout << "        Shaders = " << (useShaders ? "yes" : "no") << std::endl;
    std::cout << "     Fullscreen = " << (fullscreen ? "yes" : "no") << std::endl;
    std::cout << "Display scale x = " << scale.x << std::endl;
    std::cout << "Display scale y = " << scale.y << std::endl;
    std::cout << std::endl;
}

bool Chronact::DecodeValueYesNo(std::string s) {
    bool v = false;

    if (s == "yes")
        v = true;
    else if (s == "no")
        v = false;
    else {
        std::cout << "WARNING: Value was not 'yes' or 'no'. Defaulting to 'no'" << std::endl;
        v = false;
    }

    return v;
}

float Chronact::DecodeValueFloat(std::string s) {
    return std::atof(s.c_str());
}
