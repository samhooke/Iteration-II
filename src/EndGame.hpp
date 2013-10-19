#ifndef ENDGAME_HPP_INCLUDED
#define ENDGAME_HPP_INCLUDED

#include "GameEngine.hpp"
#include "LevelManager.hpp"

enum class EndReason {Meltdown, Victory};

class EndGame {
private:
    bool ended = false;
    EndReason endReason;
public:
    EndGame();
    ~EndGame();

    void Meltdown();
    void Victory();

    bool Ended();
    EndReason GetEndReason();
    void UpdateDisplay(GameEngine* game, LevelManager* levelManager);
};

#endif // ENDGAME_HPP_INCLUDED
