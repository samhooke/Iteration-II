#include "LevelTile.hpp"
#include "Tiles.hpp"

LevelTile::LevelTile(TileType type) {
    this->type = type;
    displayCharacter = TILE_BLANK;
}

void LevelTile::CalculateDisplayCharacter() {
    //TODO: Generate the walls properly
    if (type == TileType::Wall)
        displayCharacter = TILE_HASH;
    else
        displayCharacter = TILE_BLANK;
}
