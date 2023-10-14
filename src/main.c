#include "raylib.h"
#include "ui.h"
int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000; //GetMonitorWidth(0);
    const int screenHeight = 600;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //struct UI_TEXT_FIELD uitf = UI_TEXT_FIELD(23,23,"eeee",25,BLACK);
    struct UI_FILEIO uifilemanager = UI_FILEIO(3,3,BLACK);

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //Font f = LoadFont(".ttf");
   
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //if(IsKeyDown(KEY_S))
       
        BeginDrawing();
        ClearBackground(BLUE);
        //UI_TEXT_FIELD_draw(&uitf);
        UI_FILEIO_draw(&uifilemanager,FR_BEL_VAR);
        //UI_EXPLORER_draw(&uiexp);
        EndDrawing();
    }
   // UnloadModel(model);
    CloseWindow();        // Close window and OpenGL
    UI_FILEIO_free(&uifilemanager);
    return 0;
}

