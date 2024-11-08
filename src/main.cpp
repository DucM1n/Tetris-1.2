#include <raylib.h> // Include raylib library
#include "Game.h"
#include "Colors.h"
#include <iostream>

typedef enum GameScreen {TITLE = 0, HOW_TO, GAMEPLAY, PAUSE, ENDING} GameScreen;
double lastUpdateTime = 0;

bool EventTrigger(double interval) // Set game pace, higher interval = slower pace
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
    InitWindow(650, 820, "raylib Tetris C++"); // Initialization

    // GameScreen currentScreen = TITLE;

    SetTargetFPS(60); // Set desired framerate (frames-per-second)

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game(); // Call game class constructor
    
    while(WindowShouldClose() == false) // Game loop
    {
        
        UpdateMusicStream(game.music);
        game.HandleInput();
        
        if (!game.gamePause)
        {
            DrawTextEx(font, "Press ENTER", {420, 500}, 20, 2, WHITE);
            DrawTextEx(font, "to Play", {420, 525}, 20, 2, WHITE);           
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {480, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {490, 175}, 38, 2, WHITE);

        if (game.gameOver) 
        {
            DrawTextEx(font, "GAME OVER", {420, 500}, 29, 2, WHITE);
            DrawTextEx(font, "Press ENTER", {420, 550}, 20, 2, WHITE);
            DrawTextEx(font, "to Restart", {420, 575}, 20, 2, WHITE);
        }

        DrawRectangleRounded({420, 55, 220, 63}, 0.3, 6, lightBlue);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {420 + (220 - textSize.x) / 2, 70}, 38, 2, WHITE);
        DrawRectangleRounded({420, 215, 220, 230}, 0.3, 6, lightBlue);
        game.Draw();
        EndDrawing();
    
        if (EventTrigger(0.5))
        {
            if (game.gamePause)
            {
                game.MoveBlockDown();
            }
        }
    }
    
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
