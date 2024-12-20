#include "Game.h"
#include <random>
#include <raylib.h>
#include <iostream>
using namespace std;

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks(); 
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    high_score = LoadHighScore();
    InitAudioDevice();
    music = LoadMusicStream("Sounds/Herding Pidgeons.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/question.wav");
    clearSound = LoadSound("Sounds/Pickup Coin.wav");
    fallSound = LoadSound("Sounds/game_over.mp3");
    game_over = LoadSound("Sounds/fall.wav");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadSound(fallSound);
    UnloadSound(game_over);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch(nextBlock.id)
    {
    case 3:
        nextBlock.Draw(330, 405);
        break;
    case 4:
        nextBlock.Draw(330, 385);
        break;
    default:
        nextBlock.Draw(350, 385);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    
    if (keyPressed != 0 && gameOver)
    {
        gameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        if (!gameOver) {
            UpdateScore(0, 1);
        }
        break;
    case KEY_UP:
        RotateBlock();
        break;  
    case KEY_ENTER:
        Reset();
        break;  
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        } 
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else 
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
        PlaySound(game_over);
    }
    else {
        PlaySound(fallSound);
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
    
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch(linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }
    score += moveDownPoints;

    CheckScore();
}

void Game::CheckScore() {
    if (score > high_score ) {
        high_score = score;
        SaveHighScore(high_score);
    }
}

void Game::SaveHighScore(int Highscore) {
    ofstream file("highscore_file.txt");
    if (file.is_open()) {
        file << Highscore;
        file.close();
    }
    else {
        cerr << "failed to load"<<endl;
    }
}

int Game::LoadHighScore() {
    int loadscore = 0;
    ifstream file("highscore_file.txt");
    if(file.is_open()) {
        file >> loadscore;
        file.close();
    }
    else {
        cerr << "failed to load"<<endl ;
    }
    return loadscore;
}