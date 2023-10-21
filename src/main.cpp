// Include the Raylib header for access to its functions and types
#include <raylib.h>

// Create ball class

// Ball class definition
class Ball
{
public:
    // Ball properties
    float x, y; // Position
    int speed_x, speed_y; // Speed in x and y directions
    int radius; // Radius of the ball

    // Draw the ball on the screen
    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    // Update the ball's position and handle wall collisions
    void Update()
    {
        // Update position based on speed
        x += speed_x;
        y += speed_y;

        // Check for collision with top and bottom walls
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1; // Reverse y-direction
        }

        // Check for collision with left and right walls
        if (x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x *= -1; // Reverse x-direction
        }
    }
};

// Paddle class definition
class Paddle
{
protected:
    // Limit the paddle's vertical movement within the screen
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
    // Paddle properties
    float x, y; // Position
    float width, height; // Dimensions
    int speed; // Movement speed

    // Draw the paddle on the screen
    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    // Update the paddle's position based on user input
    void Update()
    {
        // Move up
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        // Move down
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        // Limit the paddle's movement
        LimitMovement();
    }
};

// CpuPaddle class definition, inheriting from Paddle
class CpuPaddle : public Paddle
{
public:
    // Update the CPU paddle's position based on the ball's y-coordinate
    void Update(int ball_y)
    {
        // Move up if the ball is above the paddle's center
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        // Move down if the ball is below or at the paddle's center
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }

        // Limit the paddle's movement
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
