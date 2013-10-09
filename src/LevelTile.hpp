#ifndef LEVELTILE_HPP_INCLUDED
#define LEVELTILE_HPP_INCLUDED

enum class TileType {Wall, Floor, Restricted};

class LevelTile {
public:
    LevelTile(TileType type);

    TileType type;
    bool connectsWithWall;
    int displayCharacter;
};

#endif // LEVELTILE_HPP_INCLUDED
