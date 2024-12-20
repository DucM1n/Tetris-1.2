#pragma once
#include "Grid.h"
#include "Blocks.cpp"
#include<fstream>

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void Pause();
    void MoveBlockDown();
    bool gameOver;
    int score;
    int high_score;
    Music music;
    Sound rotateSound;
    Sound clearSound;
    Sound fallSound;
    Sound game_over;
    void Reset();

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();

    void UpdateScore(int linesCleared, int moveDownPoints);
    Block GetRandomBlock();
    Grid grid;
    std::vector<Block> GetAllBlocks();    
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;

    void CheckScore();
    void SaveHighScore(int Highscore);
    int LoadHighScore();

};