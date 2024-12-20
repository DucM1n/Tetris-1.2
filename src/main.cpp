#include <raylib.h>
#include "Game.h"
#include "Colors.h"
#include <iostream>
#include "block.h"
#include <string>
using namespace std;

const int SCREEN_WIDTH = 650;
const int SCREEN_HEIGHT = 820;
const int TARGET_FPS = 60;

enum gameState {
   menu, 
   instruct,
   gameplay,
   Hard
};

double lastUpdateTime = 0;
double zz;
double z = 0.2;
double k = 0.2;
bool startGame = false;
bool Pause = false;

bool EventTrigger(double interval) 
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib Tetris C++");
    SetTargetFPS(TARGET_FPS); 
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Game game = Game(); 
    gameState GameState = menu;
    while (WindowShouldClose() == false)
    {
        ClearBackground(darkBlue);
        if (IsKeyPressed(KEY_SPACE)) {
            Pause = !Pause;
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            GameState = menu;
            game.Reset();
        }
        BeginDrawing();
        UpdateMusicStream(game.music);
        if (GameState == menu) {
            DrawText("TETRIS", MeasureText("TETRIS", 40) / 2, 40, 120, WHITE);
            DrawTextEx(font, "1. NEW GAME", {50, 200}, 40, 2, WHITE);
            DrawTextEx(font, "2. HOW TO PLAY", {50, 250}, 40, 2, WHITE);
            DrawTextEx(font, "3. DIFFICULTY", {50, 300}, 40, 2, WHITE);
            DrawTextEx(font, "Press 1, 2, 3 to pick :]", {50, 350}, 40, 2, WHITE);

            if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) 
            {
                GameState = gameplay;
            }
            if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) 
            {
                GameState = instruct;
            }
            if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) 
            {
                GameState = Hard;
            }
        }
        else if (GameState == gameplay) {
            DrawFPS(550, 0);
            DrawTextEx(font, "Score", {480, 15}, 38, 2, WHITE);
            DrawTextEx(font, "Highscore ", {440, 135}, 38, 2, WHITE);
            DrawTextEx(font, "Next", {490, 265}, 38, 2, WHITE);
                if (game.gameOver)
                {
                    DrawTextEx(font, "GAME OVER", {420, 550}, 30, 2, WHITE);
                    DrawTextEx(font, "Press ENTER", {420, 600}, 25, 2, WHITE);
                    DrawTextEx(font, "to return to", {420, 640}, 25, 2, WHITE);
                    DrawTextEx(font, "menu.", {420, 680}, 25, 2, WHITE);
                    DrawTextEx(font, "Press R", {420, 720}, 25, 2, WHITE);
                    DrawTextEx(font, "to play again.", {420, 760}, 25, 2, WHITE);
                    if (IsKeyPressed(KEY_R)) {
                        game.Reset();
                    }
                }
                DrawRectangleRounded({420, 55, 220, 63}, 0.3, 6, lightBlue);
                char scoreText[10];
                sprintf(scoreText, "%d", game.score);
                Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
                DrawTextEx(font, scoreText, {420 + (220 - textSize.x) / 2, 70}, 38, 2, WHITE);
                char highscore[10];
                sprintf(highscore, "%d", game.high_score);
                DrawRectangleRounded({420, 185, 220, 63}, 0.3, 6, lightBlue);
                Vector2 textSize1 = MeasureTextEx(font, highscore, 38, 2);
                DrawTextEx(font, highscore, {420 + (220 - textSize1.x) / 2, 199}, 38, 2, WHITE);
                DrawRectangleRounded({420, 315, 220, 230}, 0.3, 6, lightBlue);
                game.Draw();
            if (!Pause) {
                if (EventTrigger(z))
                {
                    game.MoveBlockDown();
                }
                game.HandleInput();
                bool x = IsKeyDown(KEY_DOWN);
                if (x) {
                    z = z - 0.03;
                }
                else {
                    z = k;
                }
            }
            if (Pause == true) {
                Rectangle pause = {110, 385, 200, 50};
                DrawRectangleRounded(pause, 0.3, 6 , lightBlue);
                DrawText("PAUSED", pause.x + 25, pause.y + 8, 38, WHITE);
            }
        }
        else if (GameState == instruct) {
            DrawTextEx(font, "Press RIGHT_KEY or LEFT_KEY to move", {30, 40}, 30, 2, WHITE);
            DrawTextEx(font, "blocks sideways.", {30, 80}, 30, 2, WHITE);
            DrawTextEx(font, "Press DOWN_KEY to move blocks downwards", {30, 120}, 30, 2, WHITE);
            DrawTextEx(font, "= win 1 POINT.", {30, 160}, 30, 2, WHITE);
            DrawTextEx(font, "Press UP_KEY to rotate block.", {30, 200}, 30, 2, WHITE);
            DrawTextEx(font, "Clear one line = win 100 POINTS.", {30, 240}, 30, 2, WHITE);
            DrawTextEx(font, "Press SPACE midgame to PAUSE.", {30, 280}, 30, 2, WHITE);
            DrawTextEx(font, "Press ENTER to return :]", {30, 320}, 30, 2, WHITE);
        }
        else if (GameState == Hard)
        {
            DrawTextEx(font, "1. EASY", {50, 50}, 40, 2, WHITE);
            if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                zz = 0.24;
                k = zz;
                GameState = menu;
            }
            DrawTextEx(font, "2. MEDIUM", {50, 100}, 40, 2, WHITE);
            if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) {
                zz = 0.18;
                k = zz;
                GameState = menu;
            }
            DrawTextEx(font, "3. HARD", {50, 150}, 40, 2, WHITE);
            if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) {
                zz = 0.11;
                k = zz;
                GameState = menu;
            }
            DrawTextEx(font, "Press 1, 2, 3 to pick :]", {50, 200}, 40, 2, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}