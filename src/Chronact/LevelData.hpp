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

    LevelTile GetTile(unsigned int x, unsigned int y);
};

#endif // LEVELDATA_HPP_INCLUDED
