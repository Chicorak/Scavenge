
#include "../include/player.hpp"
#include "raylib.h"
#include "../include/baby.hpp"
#include <vector>
#include <raymath.h>

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef enum Level { HOME = 0, SEWER, HOMES, TAVERN, FACTORY } Level;
typedef enum MomAnim { Idle = 0, LeftStep = 1, Reach = 2, RightStep = 3, Throw = 4 } MomAnim;
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

    InitAudioDevice();

    GameScreen currentScreen = LOGO;
    Level currentLevel = HOME;
    MomAnim animController = Idle;

    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    Texture2D TitleScreen = LoadTexture("../assets/gfx/TitleScreen.png");
    /* MomRat Textures*/
    Texture2D MomRat = LoadTexture("../assets/gfx/ThyRat/animMomRat.png");
    // ------

    // TODO: Initialize all required variables and load all required data here!
    /* Variables */
    player mainPlayer;

    mainPlayer.setRadius(50);
    mainPlayer.setPosition(50, 50);
    mainPlayer.SetTexture(MomRat);
    mainPlayer.SetAmmo(10);
    mainPlayer.SetDir(90);
    mainPlayer.SetSpeed(5);

    int MomframeWidth = mainPlayer.GetTexture().width/5;
    int MomframeHeight = mainPlayer.GetTexture().height;

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.target = (Vector2){ mainPlayer.getPositionX() + 20.0f, mainPlayer.getPositionY() + 20.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    Music HomesSfx = LoadMusicStream("assets/sfx/Homes.mp3");
    Music SewersSfx = LoadMusicStream("assets/sfx/Sewers.mp3");
    Music TavernSfx = LoadMusicStream("assets/sfx/Tavern.mp3");

    std::vector<baby> babies{};

    int tick = 0, tickInFps = 0, lastShotTick = 0;
    int ReloadCoolDown = 40;
    float fireDelay = 5; //in ticks, every frame is 1 tick

    int framesCounter = 0;          // Useful to count frames

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
        {
        // Update
        //----------------------------------------------------------------------------------
        Vector2 Mice = GetScreenToWorld2D(GetMousePosition(), camera);
        tick++;

        switch(currentScreen)
        {
            case LOGO:
            {
                framesCounter++;    // Count frames

                // Wait for 4 seconds (240 frames) before jumping to TITLE screen
                if (framesCounter > /*240*/ 1)
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
                    framesCounter = 0;
                }
            } break;
            case GAMEPLAY:
            {

                animController = Idle;
                // TODO: Update GAMEPLAY screen variables here!
                if (mainPlayer.GetInput())
                {
                    framesCounter++;
                    if (framesCounter < 15)
                        animController = LeftStep;
                    else if (framesCounter < 30)
                        animController = RightStep;
                    else
                        framesCounter = 0;
                }
                if (IsMouseButtonDown(0))
                    if (tick > lastShotTick + fireDelay ) {
                        mainPlayer.GetAmmo();
                        if (ReloadCoolDown == 40) {
                            lastShotTick = tick;
                            babies.push_back({mainPlayer.getPositionX(), mainPlayer.getPositionY(), mainPlayer.GetDir()});
                        }
                    }
                mainPlayer.SetDir(atan2(Mice.y - mainPlayer.getPositionY(), Mice.x - mainPlayer.getPositionX()) * RAD2DEG);

                //GetWorldToScreen2D
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
                BeginMode2D(camera);
                Rectangle sourceRec = { (float)MomframeWidth * (float)animController, 0.0f, (float)MomframeWidth, (float)MomframeHeight };

                // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
                Vector2 origin = { (float)MomframeWidth/2, (float)MomframeHeight/2 };

                switch (currentLevel)
                {
                    case HOME:

                        DrawTexturePro(mainPlayer.GetTexture(), sourceRec, Rectangle{ (float)(mainPlayer.getPositionX()), (float)(mainPlayer.getPositionY()), (float)MomframeWidth, (float)MomframeHeight }, origin, (float)mainPlayer.GetDir(), WHITE);

                        break;
                    case SEWER:
                        break;
                    case HOMES:
                        break;
                    case FACTORY:
                        break;
                }

                EndMode2D();
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