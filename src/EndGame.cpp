#include "EndGame.hpp"

#include <sstream>
#include "Display.hpp"
#include "Tiles.hpp"
#include "IterationData.hpp"

EndGame::EndGame() {
}

EndGame::~EndGame() {
}

void EndGame::Meltdown() {
    ended = true;
    endReason = EndReason::Meltdown;
}

void EndGame::Victory() {
    ended = true;
    endReason = EndReason::Victory;
}

bool EndGame::Ended() {
    return ended;
}

void EndGame::UpdateDisplay(GameEngine* game, LevelManager* levelManager) {
    if (Ended()) {
        std::ostringstream msg;
        std::ostringstream msg2;

        switch (endReason) {
            case EndReason::Meltdown:
                msg << "Meltdown";
                msg2 << "Press <Enter> to retry";
                break;
            case EndReason::Victory:
                msg << "Victory";
                msg2 << "Press <Enter> to continue";
                break;
            default:
                msg << "???ERR???";
                msg2 << "Press <Enter> to panic";
                break;
        }

        int msgLen = msg.str().length();
        int msgLen2 = msg2.str().length();

        std::ostringstream msgBox;
        for (int i = 0; i < 3 * (msgLen + 2); i++) {
            msgBox << (char)TILE_EXCLAMATION;
        }

        int x = game->display->GetWidth() / 2 - msgLen / 2;
        int x2 = game->display->GetWidth() / 2 - msgLen2 / 2;
        int y = game->display->GetHeight() / 2;

        if ((int)(game->gameClock->getElapsedTime().asSeconds() * 2) % 2 == 0) {
            game->display->WriteText(x - 1, y - 1, msgBox.str().c_str(), msgLen + 2, 3);
            game->display->WriteText(x, y, msg.str().c_str());

            game->display->WriteText(x2, y + 3, msg2.str().c_str());
        }
    }
}
