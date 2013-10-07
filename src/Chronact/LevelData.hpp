#ifndef LEVELDATA_HPP_INCLUDED
#define LEVELDATA_HPP_INCLUDED

#include <vector>
#include "Defs.hpp"
#include "LevelTile.hpp"

class LevelData {
private:
    unsigned int width;
    unsigned int height;
    std::vector<LevelTile> levelTiles;
public:
    LevelData(unsigned int width = 0, unsigned int height = 0);

    void SetTileType(unsigned int x, unsigned int y, TileType type);
    int GetTileDisplayCharacter(unsigned int x, unsigned int y);

    unsigned int GetWidth();
    unsigned int GetHeight();

    void CalculateDisplayCharacters();
};

#endif // LEVELDATA_HPP_INCLUDED
