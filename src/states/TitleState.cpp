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
    executeKey = ' ';
    reboot = false;
    executing = false;
    timeskip = 0.0f;
}

void TitleState::CleanUp(GameEngine* game) {
    game->display->DrawLogo(false);
}
void TitleState::Pause() {}
void TitleState::Resume() {}
void TitleState::ProcessInput(GameEngine* game) {
    sf::Event event;

    float time = clock.getElapsedTime().asSeconds() + timeskip;

    // Loop through all window events
    while (game->window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            game->Quit();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
                timeskip = 100.0f;
            if (event.key.code == sf::Keyboard::Escape)
                game->Quit();
            if (time > startTime + 8.5f / timeMultiplier) {
                if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Delete)
                    executeKey = ' ';
                if (event.key.code == sf::Keyboard::Y)
                    executeKey = 'Y';
                if (event.key.code == sf::Keyboard::N)
                    executeKey = 'N';
                if (event.key.code == sf::Keyboard::Return) {
                    if (executeKey == 'N') {
                        reboot = true;
                        rebootTime = time;
                    }
                    if (executeKey == 'Y') {
                        executing = true;
                        executeTime = time;
                    }
                }
            }
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

    float time = clock.getElapsedTime().asSeconds() + timeskip;

    if (time > startTime)
        game->display->DrawLogo(true, 2, 2);
    if (time > startTime + 0.1f / timeMultiplier)
        game->display->WriteText(2, 8, "UEFIBIOS(C) 2017 Chronact Systems, Inc.");
    if (time > startTime + 0.2f / timeMultiplier)
        game->display->WriteText(2, 9, "GTech RA4200-k BIOS Revision 1003");

    if (time > startTime + 0.5f / timeMultiplier)
        game->display->WriteText(2, 11, "Main Processor : Amtel CPU 4.33GHz");
    //game->display->WriteText(2, 12, "Installed Memory : 32768M OK");
    if (time > startTime + 0.55f / timeMultiplier) {
        std::ostringstream msg;
        msg << "Installed Memory : " << memCount;

        if (memCount < memCountMax && memCountTimeLastStep + (0.05f / timeMultiplier) < time) {
            memCount += memCountStep;
            memCountTimeLastStep = time;
        }

        if (memCount == memCountMax) {
            msg << " OK";
        }

        game->display->WriteText(2, 12, msg.str().c_str());
    }

    if (time > startTime + 1.7f / timeMultiplier)
    game->display->WriteText(2, 13, "Memory Frequency : 2333MHz");

    //game->display->WriteText(2, 15, "Detecting Primary Master    . . . DIGATE 662J18");
    if (time > startTime + 2.0f / timeMultiplier) {
        std::ostringstream msg;
        msg << "Detecting Primary Master    ";

        if (dotCount[0] < 4 && dotTime[0] + (0.1f / timeMultiplier) < time) {
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
    if (time > startTime + 2.7f / timeMultiplier) {
        std::ostringstream msg;
        msg << "Detecting Primary Slave     ";

        if (dotCount[1] < 4 && dotTime[1] + (0.1f / timeMultiplier) < time) {
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
    if (time > startTime + 3.4f / timeMultiplier) {
        std::ostringstream msg;
        msg << "Detecting Network Interface ";

        if (dotCount[2] < 4 && dotTime[2] + (0.1f / timeMultiplier) < time) {
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
    if (time > startTime + 4.1f / timeMultiplier) {
        std::ostringstream msg;
        msg << "Registering with DAWNET";

        if (dotCount[3] < 6 && dotTime[3] + (0.2f / timeMultiplier) < time) {
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

    if (time > startTime + 5.6f / timeMultiplier)
        game->display->WriteText(2, 20, "Connection established");

    if (time > startTime + 6.2f / timeMultiplier)
        game->display->WriteText(2, 22, "Data inbound from 2001:0DBB:AC10:FE01::");

    //game->display->WriteText(2, 23, "Demodulating   [############] 100%");
    if (time > startTime + 6.4f / timeMultiplier) {

        if (progressCount[0] < 100 && (progressTime[0] + (1.0f / timeMultiplier)) < time) {
            progressCount[0] += 10;
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
    if (time > startTime + 7.2f / timeMultiplier) {

        if (progressCount[1] < 100 && (progressTime[1] + (1.0f / timeMultiplier)) < time) {
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

    if (time > startTime + 8.5f / timeMultiplier) {
        game->display->WriteText(2, 26, "Execute decoded data file ITERA~II? [Y/N]");

        std::ostringstream msg;
        msg << ">";
        if (executeKey == ' ') {
            if ((int) (time / 0.5f) % 2 == 0)
                msg << "_";
        } else {
            msg << executeKey;
        }

        game->display->WriteText(2, 27, msg.str().c_str());
    }

    if (reboot) {
        game->display->WriteText(2, 29, "FATAL ERROR");
        game->display->WriteText(2, 30, "REBOOTING...");
        if (time > rebootTime + 1.0f)
            game->ChangeState(TitleState::Instance());
    }

    if (executing) {
        game->display->WriteText(2, 29, "EXECUTING...");
        if (time > executeTime + 0.5f)
            game->content->LoadNext();
            //game->ChangeState(PlayState::Instance());
    }

    game->display->Render(game);
    game->window->display();
}
