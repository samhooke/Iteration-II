#include <sstream>
#include "Timeline.hpp"
#include "Display.hpp"
#include "Tiles.hpp"

Timeline::Timeline() {}

Timeline::~Timeline() {}

void Timeline::SetTMinus(std::string meltdownTMinus, std::string catastropheTMinus) {
    this->meltdownTMinus = meltdownTMinus;
    this->catastropheTMinus = catastropheTMinus;
}

void Timeline::UpdateDisplay(GameEngine* game) {
    // Draw the box outline
    for (int xx = 0; xx < width; xx++) {
        for (int yy = 0; yy < height; yy++) {
            if (yy == 0 || yy == height - 1 || yy == height - 3)
                game->display->SetDisplayCharacter(xx + x, yy + y, TILE_X_UPPER);
            else if (xx == 0 || xx == width - 1 || (yy == height - 2 && xx == width/2))
                game->display->SetDisplayCharacter(xx + x, yy + y, TILE_X_UPPER);
        }
    }

    std::ostringstream meltdown;
    std::ostringstream catastrophe;
    meltdown << "Meltdown: " << meltdownTMinus;
    catastrophe << "Catastrophe: " << catastropheTMinus;

    game->display->WriteText(x + 3, y + height - 2, meltdown.str().c_str());
    game->display->WriteText(x + 20, y + height - 2, catastrophe.str().c_str());
    game->display->WriteText(x + 53, y + height - 2, "Iteration: b/d");
}
