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

    void DestroyAllObjects();

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

    int CreatePlayerOriginal(int x, int y);
    int CreatePlayer(int x, int y, bool hasControl, GameObject::Player* parent, int expiryTime);
    int CreateDoor(int x, int y, bool requiresKey);
    int CreateLever(int x, int y, bool state);
    int CreateWindow(int x, int y);
    int CreateTerminal(int x, int y);
    int CreateTimeMachine(int x, int y);
    int CreateRadiation(int x, int y, int intensity);
};

#endif // LEVELDATA_HPP_INCLUDED
