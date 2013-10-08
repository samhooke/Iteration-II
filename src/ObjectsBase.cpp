#include "ObjectsBase.hpp"
#include "Display.hpp"
#include <iostream>

namespace GameObject {
    bool Dynamic::SetPos(unsigned int x, unsigned int y) {
        if (x >= 0 && x < game->display->GetWidth() && y >= 0 && y < game->display->GetHeight()) {
            this->x = x;
            this->y = y;
            return true;
        }
        return false;

    }

    bool Dynamic::SetPosRelative(unsigned int x, unsigned int y) {
        return SetPos(this->x + x, this->y + y);
    }
}
