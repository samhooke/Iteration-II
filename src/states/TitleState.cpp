#include <iostream>
#include "../Chronact.hpp"
#include "TitleState.hpp"
#include "PlayState.hpp"
#include "../Tiles.hpp"

TitleState TitleState::m_TitleState;

void TitleState::Init(GameEngine* game) {}
void TitleState::CleanUp(GameEngine* game) {
    game->display->DrawLogo(false);
}
void TitleState::Pause() {}
void TitleState::Resume() {}
void TitleState::ProcessInput(GameEngine* game) {
    sf::Event event;

    // Loop through all window events
    while (game->window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            game->Quit();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Return)
                game->ChangeState(PlayState::Instance());
            if (event.key.code == sf::Keyboard::Escape)
                game->Quit();
            break;
        default:
            break;
        }
    }
}

void TitleState::Update(GameEngine* game) {
}

void TitleState::RenderFrame(GameEngine* game) {
    game->window->clear();

    game->display->SetAll(TILE_BLANK);

    game->display->DrawLogo(true, 2, 2);
    game->display->WriteText(2, 8, "UEFIBIOS(C) 2017 Chronact Systems, Inc.");
    game->display->WriteText(2, 9, "GTech RA4200-k BIOS Revision 1003");

    game->display->WriteText(2, 11, "Main Processor : Amtel CPU 4.33GHz");
    game->display->WriteText(2, 12, "Installed Memory : 32768M OK");
    game->display->WriteText(2, 13, "Memory Frequency : 2333MHz");

    game->display->WriteText(2, 15, "Detecting Primary Master    . . . DIGATE 662J18");
    game->display->WriteText(2, 16, "Detecting Primary Slave     . . . None");
    game->display->WriteText(2, 17, "Detecting Network Interface . . . ZETACORP M-ETH/5");

    game->display->WriteText(2, 19, "Registering with DAWNET... OK");
    game->display->WriteText(2, 20, "Connection established");

    game->display->WriteText(2, 22, "Data inbound from 2001:0DBB:AC10:FE01::");
    game->display->WriteText(2, 23, "Demodulating   [############] 100%");
    game->display->WriteText(2, 24, "Decoding       [########    ] 65%");

    game->display->Render(game);
    game->window->display();
}
