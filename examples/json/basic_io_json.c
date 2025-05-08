#include "raylib.h"

int main(void)
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 450;

    InitWindow(ScreenWidth, ScreenHeight, "RFW [rJSON] example - Basic IO");


    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    int MyDogsAge = 0;
    float MyDogsHeight = 0.0f;

    JsonData JsonExample = LoadJSON("resources/Example.json");

    JSONSetDefaultRoot(&JsonExample); // Set Default Root

    JSONSetRoot(&JsonExample, "Dogs"); // Change Roots
        JSONSetRoot(&JsonExample, "Dog1");
            MyDogsAge = JSONFindInteger(&JsonExample, "Age"); // Pull Data from the File
            MyDogsHeight = JSONFindFloat(&JsonExample, "Height");

    // Main game loop
    while (!WindowShouldClose()) 
    {

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Loaded From a JSON File", 20, 20, 20, PURPLE);

            DrawText(TextFormat("My Dog is %i Year Old", MyDogsAge), 20, 60, 20, RED);
            DrawText(TextFormat("My Dog is %fcm Tall", MyDogsHeight), 20, 100, 20, RED);
            DrawText(TextFormat("My Dog Name is %s", JSONFindString(&JsonExample, "Name")), 20, 140, 20, RED);

        EndDrawing();

    }
    UnloadJSON(JsonExample);

    CloseWindow();       
    return 0;
}