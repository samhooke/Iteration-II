#include "Chronact.hpp"

#include <string>
#include <fstream>
#include "Logger.hpp"
#include "Defs.hpp"

#ifdef OS_WINDOWS
#include <windows.h>
void Chronact::Pause() {
    Sleep(SLEEP_MILLISECONDS);
}
#endif // OS_WINDOWS

#ifdef OS_UNIX
#include <unistd.h>
void Chronact::Pause() {
    usleep(SLEEP_MILLISECONDS * 1000);
}
#endif // OS_UNIX

Chronact::Chronact() {
}

Chronact::~Chronact() {
    // Clear used resources
    delete display;
    delete window;
}

bool Chronact::Init() {
    // Start the game clock
    gameClock.restart();

    // Create graphical interfaces
    display = new Display(useShaders);
    window = new sf::RenderWindow(sf::VideoMode(display->GetPixelWidth(), display->GetPixelHeight(), 32), "Iteration II", sf::Style::Default); // ::Close to disable resizing

    // Verify the window was created
    if (!window)
        return false;

    return true;
}

void Chronact::RenderFrame() {
    window->clear();
    display->Render(window, &gameClock);
    window->display();
}

void Chronact::ProcessInput() {
    sf::Event event;

    // Loop through all window events
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Chronact::MainLoop() {
    // Loop until our window is closed
    while (window->isOpen()) {
        deltaTime = deltaClock.restart();
        ProcessInput();
        Update();
        Pause();
        RenderFrame();
    }
}

void Chronact::Go() {
    printf("Reading config.txt file\n");

    ReadConfig();

    printf("Running Chronact engine\n");

    if (!Init())
        throw EngineInitError();

    room = Room::Title;
    RoomStart();

    MainLoop();
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

void Chronact::Update() {
    RoomUpdate();
}

void Chronact::RoomStart() {
    switch (room) {
    case Room::Title:       RoomTitle(RoomEvent::Start);        break;
    case Room::Blank:       RoomBlank(RoomEvent::Start);        break;
    }
}

void Chronact::RoomUpdate() {
    switch (room) {
    case Room::Title:       RoomTitle(RoomEvent::Update);        break;
    case Room::Blank:       RoomBlank(RoomEvent::Update);        break;
    }
}

void Chronact::RoomEnd() {
    switch (room) {
    case Room::Title:       RoomTitle(RoomEvent::End);        break;
    case Room::Blank:       RoomBlank(RoomEvent::End);        break;
    }
}

void Chronact::RoomTitle(RoomEvent roomEvent) {
    static float timeSinceLastDraw = 0;
    switch (roomEvent) {
    case RoomEvent::Start:
        break;
    case RoomEvent::Update:
        timeSinceLastDraw += deltaTime.asSeconds();
        if (timeSinceLastDraw > (float)1/60) {
            display->DrawBackground();
            display->DrawTitle();
            timeSinceLastDraw = 0;
        }
        break;
    case RoomEvent::End:
        break;
    }
}

void Chronact::RoomBlank(RoomEvent roomEvent) {
    display->DrawBackground();
}
