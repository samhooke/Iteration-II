#include "LevelData.hpp"
#include "Tiles.hpp"
#include <iostream>

#include <stdio.h>

LevelData::LevelData() {
    for (unsigned int i = 0; i < width * height; i++) {
        levelTiles.push_back(LevelTile(TileType::Floor));
    }
}

void LevelData::SetTileDetails(unsigned int x, unsigned int y, TileType type) {
    unsigned int index = x + y * width;
    levelTiles[index].type = type;

    // Also set other details
    levelTiles[index].connectsWithWall = (type == TileType::Wall || type == TileType::Door);
}

int LevelData::GetTileDisplayCharacter(unsigned int x, unsigned int y) {
    unsigned int index = x + y * width;
    return levelTiles[index].displayCharacter;
}

void LevelData::CalculateDisplayCharacters() {
    bool wall_n, wall_e, wall_s, wall_w;
    int index_n, index_e, index_s, index_w;
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            int index = x + y * width;

            index_n = x + (y - 1) * width;
            index_e = (x + 1) + y * width;
            index_s = x + (y + 1) * width;
            index_w = (x - 1) + y * width;

            wall_n = wall_e = wall_s = wall_w = false;

            if (y >= 1)         {wall_n = (levelTiles[index_n].connectsWithWall);} else {wall_n = false;}
            if (x < width - 1)  {wall_e = (levelTiles[index_e].connectsWithWall);} else {wall_e = false;}
            if (y < height - 1) {wall_s = (levelTiles[index_s].connectsWithWall);} else {wall_s = false;}
            if (x >= 1)         {wall_w = (levelTiles[index_w].connectsWithWall);} else {wall_w = false;}

            int c = TILE_QUESTION; // Default is question mark

            if (levelTiles[index].type == TileType::Wall) {

                int wallMask = ((int)wall_n) | ((int)wall_e << 1) | ((int)wall_s << 2) | ((int)wall_w << 3);

                switch (wallMask) {
                case 0b0000:    c = TILE_WD_PILLAR; break;
                case 0b0001:    c = TILE_WD_N;      break;
                case 0b0010:    c = TILE_WD_E;      break;
                case 0b0011:    c = TILE_WD_NE;     break;
                case 0b0100:    c = TILE_WD_S;      break;
                case 0b0101:    c = TILE_WD_NS;     break;
                case 0b0110:    c = TILE_WD_ES;     break;
                case 0b0111:    c = TILE_WD_NES;    break;
                case 0b1000:    c = TILE_WD_W;      break;
                case 0b1001:    c = TILE_WD_NW;     break;
                case 0b1010:    c = TILE_WD_EW;     break;
                case 0b1011:    c = TILE_WD_NEW;    break;
                case 0b1100:    c = TILE_WD_SW;     break;
                case 0b1101:    c = TILE_WD_NSW;    break;
                case 0b1110:    c = TILE_WD_ESW;    break;
                case 0b1111:    c = TILE_WD_NESW;   break;
                default:        c = TILE_QUESTION;  break; // Error
                }
            } else if (levelTiles[index].type == TileType::Door) {
                c = TILE_DOOR;
            } else if (levelTiles[index].type == TileType::Floor) {
                c = TILE_BLANK;
            }

            levelTiles[index].displayCharacter = c;
        }
    }
}

unsigned int LevelData::GetWidth() {
    return width;
}

unsigned int LevelData::GetHeight() {
    return height;
}
