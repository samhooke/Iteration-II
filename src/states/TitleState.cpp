#include <iostream>
#include "../Chronact.hpp"
#include "TitleState.hpp"
#include "PlayState.hpp"
#include "../Tiles.hpp"
#include <sstream>

TitleState TitleState::m_TitleState;

void TitleState::Init(GameEngine* game) {
    clock.restart();
    memCountTimeLastStep = dotTime[0] = dotTime[1] = dotTime[2] = dotTime[3] = progressTime[0] = progressTime[1] = clock.getElapsedTime().asSeconds();
    memCount = 0;
    dotCount[0] = dotCount[1] = dotCount[2] = dotCount[3] = -1;
    progressCount[0] = progressCount[1] = 0;
}

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

    float time = clock.getElapsedTime().asSeconds();
    float startTime = 1.5f;

    if (time > startTime)
        game->display->DrawLogo(true, 2, 2);
    if (time > startTime + 0.1f)
        game->display->WriteText(2, 8, "UEFIBIOS(C) 2017 Chronact Systems, Inc.");
    if (time > startTime + 0.2f)
        game->display->WriteText(2, 9, "GTech RA4200-k BIOS Revision 1003");

    if (time > startTime + 0.5f)
        game->display->WriteText(2, 11, "Main Processor : Amtel CPU 4.33GHz");
    //game->display->WriteText(2, 12, "Installed Memory : 32768M OK");
    if (time > startTime + 0.55f) {
        std::ostringstream msg;
        msg << "Installed Memory : " << memCount;

        if (memCount < memCountMax && memCountTimeLastStep + 0.05f < time) {
            memCount += memCountStep;
            memCountTimeLastStep = time;
        }

        if (memCount == memCountMax) {
            msg << " OK";
        }

        game->display->WriteText(2, 12, msg.str().c_str());
    }

    if (time > startTime + 1.7f)
    game->display->WriteText(2, 13, "Memory Frequency : 2333MHz");

    //game->display->WriteText(2, 15, "Detecting Primary Master    . . . DIGATE 662J18");
    if (time > startTime + 2.0f) {
        std::ostringstream msg;
        msg << "Detecting Primary Master    ";

        if (dotCount[0] < 4 && dotTime[0] + 0.1f < time) {
            dotCount[0] += 1;
            dotTime[0] = time;
        }

        for (int i = 0; i < dotCount[0]; i++) {
            if (i < 3)
                msg << " .";
            else
                msg << "DIGATE 662J18";
        }
        game->display->WriteText(2, 15, msg.str().c_str());
    }

    //game->display->WriteText(2, 16, "Detecting Primary Slave     . . . None");
    if (time > startTime + 2.7f) {
        std::ostringstream msg;
        msg << "Detecting Primary Slave     ";

        if (dotCount[1] < 4 && dotTime[1] + 0.1f < time) {
            dotCount[1] += 1;
            dotTime[1] = time;
        }

        for (int i = 0; i < dotCount[1]; i++) {
            if (i < 3)
                msg << " .";
            else
                msg << "None";
        }
        game->display->WriteText(2, 16, msg.str().c_str());
    }

    //game->display->WriteText(2, 17, "Detecting Network Interface . . . ZETACORP M-ETH/5");
    if (time > startTime + 3.4f) {
        std::ostringstream msg;
        msg << "Detecting Network Interface ";

        if (dotCount[2] < 4 && dotTime[2] + 0.1f < time) {
            dotCount[2] += 1;
            dotTime[2] = time;
        }

        for (int i = 0; i < dotCount[2]; i++) {
            if (i < 3)
                msg << " .";
            else
                msg << "ZETACORP M-ETH/5";
        }
        game->display->WriteText(2, 17, msg.str().c_str());
    }

    //game->display->WriteText(2, 19, "Registering with DAWNET..... OK");
    if (time > startTime + 4.1f) {
        std::ostringstream msg;
        msg << "Registering with DAWNET";

        if (dotCount[3] < 6 && dotTime[3] + 0.2f < time) {
            dotCount[3] += 1;
            dotTime[3] = time;
        }

        for (int i = 0; i < dotCount[3]; i++) {
            if (i < 5)
                msg << ".";
            else
                msg << " OK";
        }
        game->display->WriteText(2, 19, msg.str().c_str());
    }

    if (time > startTime + 5.6f)
        game->display->WriteText(2, 20, "Connection established");

    if (time > startTime + 6.2f)
        game->display->WriteText(2, 22, "Data inbound from 2001:0DBB:AC10:FE01::");

    //game->display->WriteText(2, 23, "Demodulating   [############] 100%");
    if (time > startTime + 6.4f) {

        if (progressCount[0] < 100 && progressTime[0] + 0.08f < time) {
            progressCount[0] += 5;
            progressTime[0] = time;
        }

        std::ostringstream msg;
        msg << "Demodulating   [";

        for (int i = 0; i < 12; i++) {
            if (progressCount[0] >= (((float)i / 12) * 100))
                msg << "#";
            else
                msg << " ";
        }

        msg << "] " << progressCount[0] << "%";

        game->display->WriteText(2, 23, msg.str().c_str());
    }

    // game->display->WriteText(2, 24, "Decoding       [########    ] 65%");
    if (time > startTime + 7.2f) {

        if (progressCount[1] < 100 && (progressTime[1] + 1.0f) < time) {
            progressCount[1] += 20;
            progressTime[1] = time;
        }

        std::ostringstream msg;
        msg << "Decoding       [";

        for (int i = 0; i < 12; i++) {
            if (progressCount[1] >= (((float)i / 12) * 100))
                msg << "#";
            else
                msg << " ";
        }

        msg << "] " << progressCount[1] << "%";

        game->display->WriteText(2, 24, msg.str().c_str());
    }

    if (time > startTime + 10.6f) {
        game->display->WriteText(2, 26, "Display decoded message? [Y/N]");

        std::ostringstream msg;
        msg << ">";
        if ((int) (time / 0.5f) % 2 == 0)
            msg << "_";

        game->display->WriteText(2, 27, msg.str().c_str());
    }

    game->display->Render(game);
    game->window->display();
}
