#ifndef LEVELDATA_HPP_INCLUDED
#define LEVELDATA_HPP_INCLUDED

#include <vector>
#include <string>
#include "Defs.hpp"
#include "LevelTile.hpp"
#include "ObjectsBase.hpp"
#include "GameEngine.hpp"
#include "objects/Player.hpp"

class LevelManager;

class LevelData {
private:
    int width = DISPLAY_WIDTH;
    int height = DISPLAY_HEIGHT;

    std::vector<LevelTile> levelTiles;
    std::vector<GameObject::Base*> levelObjects;

    GameEngine* game;
    LevelManager* levelManager;
public:
    LevelData(GameEngine* game, LevelManager* levelManager);
    ~LevelData();

    char nextCloneDesignation = 'A';

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
    GameObject::Base* GetObjectPointer(int index);
    void SetObjectHasControl(int index, bool hasControl);
    bool CompareObjectTag(int index, std::string tag);

    void CallObjectUpdate(int index);
    void CallObjectUpdateTimeChanged(int index);

    void CreatePlayerOriginal(int x, int y);
    void CreatePlayer(int x, int y, bool hasControl, GameObject::Player* parent, int expiryTime);
    void CreateDoor(int x, int y);
    void CreateWindow(int x, int y);
    void CreateTerminal(int x, int y);
    void CreateTimeMachine(int x, int y);
    void CreateRadiation(int x, int y, int intensity);

    std::string Timestamp();
};

#endif // LEVELDATA_HPP_INCLUDED
