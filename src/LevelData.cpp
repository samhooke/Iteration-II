#include <iostream>
#include "LevelData.hpp"
#include "Tiles.hpp"

#include "Player.hpp"
#include "Door.hpp"
#include "Radiation.hpp"

LevelData::LevelData(GameEngine* game) {
    // Requires a reference to GameEngine which it passes on to created objects
    this->game = game;

    for (unsigned int i = 0; i < width * height; i++) {
        levelTiles.push_back(LevelTile(TileType::Floor));
    }
}

LevelData::~LevelData() {
    // Destroy all generated GameObjects
    for (unsigned int i = 0; i < levelObjects.size(); i++) {
        delete levelObjects[i];
    }
}

void LevelData::SetTileDetails(unsigned int x, unsigned int y, TileType type, bool connectsWithWall) {
    unsigned int index = x + y * width;
    levelTiles[index].type = type;
    levelTiles[index].connectsWithWall = connectsWithWall;
}

int LevelData::GetTileDisplayCharacter(unsigned int x, unsigned int y) {
    unsigned int index = x + y * width;
    return levelTiles[index].displayCharacter;
}

TileType LevelData::GetTileType(unsigned int x, unsigned int y) {
    unsigned int index = x + y * width;
    return levelTiles[index].type;
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

int LevelData::GetNumObjects() {
    return levelObjects.size();
}

int LevelData::GetObjectDisplayCharacter(int index) {
    return levelObjects[index]->displayCharacter;
}

unsigned int LevelData::GetObjectX(int index) {
    return levelObjects[index]->x;
}

unsigned int LevelData::GetObjectY(int index) {
    return levelObjects[index]->y;
}

void LevelData::CallObjectUpdate(int index) {
    levelObjects[index]->Update();
}

void LevelData::CreatePlayer(unsigned int x, unsigned int y) {
    std::cout << "CreatePlayer(" << x << "," << y << ")" << std::endl;
    levelObjects.push_back(new GameObject::Player(x, y, game, this));
}

void LevelData::CreateDoor(unsigned int x, unsigned int y) {
    std::cout << "CreateDoor(" << x << "," << y << ")" << std::endl;
    levelObjects.push_back(new GameObject::Door(x, y, game, this));
}

void LevelData::CreateRadiation(unsigned int x, unsigned int y) {
    std::cout << "CreateRadiation(" << x << "," << y << ")" << std::endl;
    levelObjects.push_back(new GameObject::Radiation(x, y, game, this));
}
