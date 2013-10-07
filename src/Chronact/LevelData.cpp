#include "LevelData.hpp"
#include "Tiles.hpp"

LevelData::LevelData() {
    for (unsigned int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        levelTiles.push_back(LevelTile(TILE_BLANK));
    }
}

LevelTile LevelData::GetTile(unsigned int x, unsigned int y) {
    unsigned int index = x + y * DISPLAY_WIDTH;
    return levelTiles[index];
}
