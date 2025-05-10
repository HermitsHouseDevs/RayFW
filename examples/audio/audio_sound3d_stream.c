/*******************************************************************************************
*
*   raylib [audio] example - 3D Audio playback
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 5.5, last time updated with raylib 5.5
*
*   Example contributed by paganswrath (@paganswrath)
*
********************************************************************************************/
#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - 3D Audio playback");

    InitAudioDevice();              // Initialize audio device
    InitAudioSystem3D();            // Initialize 3D Audio 


    Camera3D camera = { 0 };        // Basic camera setup

    camera.position = (Vector3){ 10.0f, 2.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        
    camera.fovy = 45.0f;                     
    camera.projection = CAMERA_PERSPECTIVE;          

    Sound3D FireSound = LoadSound3D("resources/campfire.mp3"); // Load Audio 
    Vector3 FirePosition = { 0.0f, 0.0f, 0.0f };

    Texture2D FireBillboard = LoadTexture("resources/campfire.png"); // Load Texture

    PlaySound3D(FireSound, FirePosition, 100.0f, 0.0f, 20.f);

    DisableCursor();


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        UpdateAudioSystem3D(); // Update 3D Audio 
        BindListenerToCamera(camera); // Bind listener 3D to Camera 

        if (!IsSound3DPlaying(FireSound)){ // Loop sound
            PlaySound3D(FireSound, FirePosition, 100.0f, 0.0f, 20.f); // Same parameters 
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                DrawPoint3D(FirePosition, RED);
                DrawGrid(30, 1.0f);
                DrawBillboard(camera, FireBillboard, (Vector3){FirePosition.x, FirePosition.y + 1.0f, FirePosition.z}, 2.0f, WHITE);


            EndMode3D();

            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);
            DrawText("3D Audio Example:", 20, 20, 10, BLACK);
            DrawText("- Walk around to hear the fire in 3D !", 40, 40, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadAudioSystem3D();      // Frees up all the sounds automatically 

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
