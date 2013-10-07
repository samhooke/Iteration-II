#include "LevelData.hpp"
#include "Tiles.hpp"

LevelData::LevelData() {
    for (unsigned int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        levelTiles.push_back(LevelTile(TileType::Floor));
    }
}

void LevelData::SetTileType(unsigned int x, unsigned int y, TileType type) {
    unsigned int index = x + y * DISPLAY_WIDTH;
    levelTiles[index].type = type;
}

int LevelData::GetTileDisplayCharacter(unsigned int x, unsigned int y) {
    unsigned int index = x + y * DISPLAY_WIDTH;
    return levelTiles[index].displayCharacter;
}

void LevelData::CalculateDisplayCharacters() {
    for (unsigned int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        levelTiles[i].CalculateDisplayCharacter();
    }
}
