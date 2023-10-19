// Include the Raylib header for access to its functions and types
#include <raylib.h>

// Entry point for the program
int main()
{
    // Define the screen dimensions
    const int screen_width = 1280;
    const int screen_height = 800;

    // Initialize the window with the given dimensions and title
    InitWindow(screen_width, screen_height, "My Pong Game");

    // Set the target frames per second (FPS)
    SetTargetFPS(60);

    // Main game loop; continues until the window is closed
    while (WindowShouldClose() == false)
    {
        // Begin the drawing phase
        BeginDrawing();

        // Drawing circle
        DrawCircle(screen_width / 2, screen_height / 2, 20, WHITE);

        // Drwaing Rectangle
        DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
        DrawRectangle(screen_width - 35, screen_height / 2 - 60, 25, 120, WHITE);

        // Draw Court Line
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        // End the drawing phase
        EndDrawing();
    }

    // Close the window and free up resources
    CloseWindow();

    // Return 0 to indicate successful execution
    return 0;
}
