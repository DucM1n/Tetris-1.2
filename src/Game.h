#pragma once
#include "Grid.h"
#include "Blocks.cpp"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void Pause();
    void MoveBlockDown();
    bool gamePause;
    bool gameOver;
    int score;
    Music music;
    
private:
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Block GetRandomBlock();
    Grid grid;
    std::vector<Block> GetAllBlocks();    
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
    Sound fallSound;
    Sound game_over;
};