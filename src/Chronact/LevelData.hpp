#ifndef LEVELDATA_HPP_INCLUDED
#define LEVELDATA_HPP_INCLUDED

#include <vector>
#include "Defs.hpp"
#include "LevelTile.hpp"

class LevelData {
private:
    std::vector<LevelTile> levelTiles;
public:
    LevelData();

    void SetTileType(unsigned int x, unsigned int y, TileType type);
    int GetTileDisplayCharacter(unsigned int x, unsigned int y);

    void CalculateDisplayCharacters();
};

#endif // LEVELDATA_HPP_INCLUDED
