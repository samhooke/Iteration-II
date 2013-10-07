#include "LevelTile.hpp"
#include "Tiles.hpp"

LevelTile::LevelTile(TileType type) {
    this->type = type;
    displayCharacter = TILE_BLANK;
}
