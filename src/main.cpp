
#include "../include/player.hpp"
#include "raylib.h"
#include <math.h>

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

//------------------------------------------------------------------------------------------
// Main entry point
//------------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 800;

    const int virtualScreenWidth = 320;
    const int virtualScreenHeight = 180;

    const float virtualRatio = (float)screenWidth/(float)virtualScreenWidth;

    InitWindow(screenWidth, screenHeight, "Scavenge");

    GameScreen currentScreen = LOGO;

    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    Texture2D TitleScreen = LoadTexture("../assets/gfx/TitleScreen.png");
    /* MomRat Textures*/
    Texture2D MomRatIdle = LoadTexture("../assets/gfx/ThyRat/MomRatIdle.png");
    Texture2D MomRatLeftstep = LoadTexture("../assets/gfx/ThyRat/MomRatLeftstep.png");
    Texture2D MomRatRightstep = LoadTexture("../assets/gfx/ThyRat/MomRatRightstep.png");
    Texture2D MomRatReach = LoadTexture("../assets/gfx/ThyRat/MomRatReach.png");
    Texture2D MomRatThrow = LoadTexture("../assets/gfx/ThyRat/MomRatThrow.png");
    // ------

    // TODO: Initialize all required variables and load all required data here!
    /* Variables */
    player mainPlayer{};

    mainPlayer.setRadius(50);
    mainPlayer.setPosition(50, 50);
    mainPlayer.SetTexture(MomRatIdle);
    mainPlayer.SetDir(0);
    mainPlayer.SetSpeed(2);

    int framesCounter = 0;          // Useful to count frames

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
        {
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case LOGO:
            {
                framesCounter++;    // Count frames

                // Wait for 4 seconds (240 frames) before jumping to TITLE screen
                if (framesCounter > 240)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!
                mainPlayer.GetInput();
                mainPlayer.SetDir(atan2(GetMouseY(), GetMouseX()) * DEG2RAD);

            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);

        switch(currentScreen)
        {
            case LOGO:
            {
                DrawTexture(TitleScreen, 0, 0,  WHITE);

            } break;
            case TITLE:
            {
                // TODO: Draw TITLE screen here!
                DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", screenWidth/2 - 150, screenHeight/2, 20, DARKGREEN);

            } break;
            case GAMEPLAY:
            {
                DrawTextureEx(mainPlayer.GetTexture(), Vector2{(float)mainPlayer.getPositionX(), (float)mainPlayer.getPositionY()}, (int)mainPlayer.GetDir(), 1.0f, WHITE);
            } break;
            case ENDING:
            {
                // TODO: Draw ENDING screen here!
                DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", screenWidth/2 - 100, screenHeight/2, 20, DARKBLUE);

            } break;
            default: break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
        }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!
    UnloadRenderTexture(target);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}