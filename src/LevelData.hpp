#ifndef LEVELDATA_HPP_INCLUDED
#define LEVELDATA_HPP_INCLUDED

#include <vector>
#include "Defs.hpp"
#include "LevelTile.hpp"
#include "ObjectsBase.hpp"

class LevelData {
private:
    unsigned int width = DISPLAY_WIDTH;
    unsigned int height = DISPLAY_HEIGHT;
    std::vector<LevelTile> levelTiles;
    std::vector<GameObject::Base*> levelObjects;
public:
    LevelData();
    ~LevelData();

    void SetTileDetails(unsigned int x, unsigned int y, TileType type, bool connectsWithWall);
    int GetTileDisplayCharacter(unsigned int x, unsigned int y);

    unsigned int GetWidth();
    unsigned int GetHeight();

    void CalculateDisplayCharacters();

    int GetNumObjects();
    int GetObjectDisplayCharacter(int index);
    unsigned int GetObjectX(int index);
    unsigned int GetObjectY(int index);

    void CreatePlayer(unsigned int x, unsigned int y);
    void CreateDoor(unsigned int x, unsigned int y);
};

#endif // LEVELDATA_HPP_INCLUDED
