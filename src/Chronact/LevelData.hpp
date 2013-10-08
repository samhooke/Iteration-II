#ifndef LEVELDATA_HPP_INCLUDED
#define LEVELDATA_HPP_INCLUDED

#include <vector>
#include "Defs.hpp"
#include "LevelTile.hpp"

class LevelData {
private:
    unsigned int width = DISPLAY_WIDTH;
    unsigned int height = DISPLAY_HEIGHT;
    std::vector<LevelTile> levelTiles;
public:
    LevelData();

    void SetTileDetails(unsigned int x, unsigned int y, TileType type);
    int GetTileDisplayCharacter(unsigned int x, unsigned int y);

    unsigned int GetWidth();
    unsigned int GetHeight();

    void CalculateDisplayCharacters();
};

#endif // LEVELDATA_HPP_INCLUDED
