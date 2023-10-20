// Include the Raylib header for access to its functions and types
#include <raylib.h>

// Create ball class

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }

        if (x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x *= -1;
        }
    }
};

class Paddle
{

protected:

    void LimitMovement() {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

class CpuPaddle : public Paddle
{
public:
    void Update(int ball_y)
    {

        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

// Create ball object
Ball ball;

//  Create paddle object
Paddle player;
CpuPaddle cpu;

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

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    // Main game loop; continues until the window is closed
    while (WindowShouldClose() == false)
    {
        // Begin the drawing phase
        BeginDrawing();

        // Ball movement, just updating ball position
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Clearing Background
        ClearBackground(BLACK);

        // Drawing circle
        ball.Draw();

        // Drwaing Rectangle
        cpu.Draw();
        player.Draw();

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
