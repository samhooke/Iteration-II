#include "LevelData.hpp"
#include "Tiles.hpp"
#include <iostream>

LevelData::LevelData(unsigned int width, unsigned int height) {
    //std::cout << "Created LevelData with dimensions " << width << "x" << height << std::endl;
    this->width = width;
    this->height = height;
    for (unsigned int i = 0; i < width * height; i++) {
        levelTiles.push_back(LevelTile(TileType::Floor));
    }
}

void LevelData::SetTileType(unsigned int x, unsigned int y, TileType type) {
    unsigned int index = x + y * width;
    levelTiles[index].type = type;
}

int LevelData::GetTileDisplayCharacter(unsigned int x, unsigned int y) {
    unsigned int index = x + y * width;
    return levelTiles[index].displayCharacter;
}

void LevelData::CalculateDisplayCharacters() {
    for (unsigned int i = 0; i < width * height; i++) {
        levelTiles[i].CalculateDisplayCharacter();
    }
}

unsigned int LevelData::GetWidth() {
    return width;
}

unsigned int LevelData::GetHeight() {
    return height;
}
