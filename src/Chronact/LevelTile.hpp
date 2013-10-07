#ifndef LEVELTILE_HPP_INCLUDED
#define LEVELTILE_HPP_INCLUDED

enum class TileType {Wall, Floor};

class LevelTile {
public:
    LevelTile(TileType type);

    TileType type;
    int displayCharacter;

    void CalculateDisplayCharacter();
};

#endif // LEVELTILE_HPP_INCLUDED
