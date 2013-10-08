#include "LevelTile.hpp"
#include "Tiles.hpp"

LevelTile::LevelTile(TileType type) {
    this->type = type;

    // Set default characteristics. These should be overridden manually
    displayCharacter = TILE_BLANK;
    connectsWithWall = false;
}
