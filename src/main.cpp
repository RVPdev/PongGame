#include <raylib.h>

int main()
{
    const int screen_width = 1280;
    const int screen_heigth = 800;

    InitWindow(screen_width, screen_heigth, "My Pong Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {

        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}