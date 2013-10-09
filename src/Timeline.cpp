#include "Timeline.hpp"
#include "Display.hpp"
#include "Tiles.hpp"

Timeline::Timeline() {}

Timeline::~Timeline() {}

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

    game->display->WriteText(x + 13, y + height - 2, "Meltdown: T-17");
    game->display->WriteText(x + 53, y + height - 2, "Iteration: 4");
}
