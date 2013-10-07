#include "LevelTile.hpp"

LevelTile::LevelTile(char tileRender) {
    this->tileRender = tileRender;
}

char LevelTile::GetTileRender() {
    return tileRender;
}
