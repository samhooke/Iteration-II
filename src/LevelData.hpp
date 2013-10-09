#ifndef LEVELDATA_HPP_INCLUDED
#define LEVELDATA_HPP_INCLUDED

#include <vector>
#include "Defs.hpp"
#include "LevelTile.hpp"
#include "ObjectsBase.hpp"
#include "GameEngine.hpp"

class LevelData {
private:
    int width = DISPLAY_WIDTH;
    int height = DISPLAY_HEIGHT;
    std::vector<LevelTile> levelTiles;
    std::vector<GameObject::Base*> levelObjects;
    GameEngine* game;
public:
    LevelData(GameEngine* game);
    ~LevelData();

    void CreateBlankLevel(int width, int height);

    void SetTileDetails(int x, int y, TileType type, bool connectsWithWall);
    int GetTileDisplayCharacter(int x, int y);
    TileType GetTileType(int x, int y);

    int GetWidth();
    int GetHeight();

    void CalculateDisplayCharacters();

    int GetNumObjects();
    int GetObjectDisplayCharacter(int index);
    int GetObjectX(int index);
    int GetObjectY(int index);
    void CallObjectUpdate(int index);

    void CreatePlayer(int x, int y);
    void CreateDoor(int x, int y);
    void CreateRadiation(int x, int y);
};

#endif // LEVELDATA_HPP_INCLUDED
