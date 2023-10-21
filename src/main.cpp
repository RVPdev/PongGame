// Include the Raylib header for access to its functions and types
#include <raylib.h>

// score
int player_score = 0;
int cpu_score = 0;

// Ball class definition
class Ball
{
public:
    // Ball properties
    float x, y;           // Position
    int speed_x, speed_y; // Speed in x and y directions
    int radius;           // Radius of the ball

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
        if (x + radius >= GetScreenWidth()) //* Cpus scores a point
        {
            cpu_score++;
            ResetBall();
        }
        if (x - radius <= 0) //* Player scores a point
        {
            player_score++;
            ResetBall();
        }
    }

    // Reset the ball's position and speed
    void ResetBall()
    {
        // Reset the ball's x-coordinate to the horizontal center of the screen
        x = GetScreenWidth() / 2;

        // Reset the ball's y-coordinate to the vertical center of the screen
        y = GetScreenHeight() / 2;

        // Array containing two choices for speed direction: -1 or 1
        int speed_choices[2] = {-1, 1};

        // Randomly set the ball's horizontal speed direction
        speed_x *= speed_choices[GetRandomValue(0, 1)];

        // Randomly set the ball's vertical speed direction
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

// Paddle class definition
class Paddle
{
protected:
    // Limit the paddle's vertical movement within the screen
    void LimitMovement()
    {
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
    float x, y;          // Position
    float width, height; // Dimensions
    int speed;           // Movement speed

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

    // Initialize Ball attributes
    ball.radius = 20;           // Set the radius of the ball to 20 units
    ball.x = screen_width / 2;  // Start the ball at the horizontal center of the screen
    ball.y = screen_height / 2; // Start the ball at the vertical center of the screen
    ball.speed_x = 7;           // Set the ball's horizontal speed to 7 units per frame
    ball.speed_y = 7;           // Set the ball's vertical speed to 7 units per frame

    // Initialize Player Paddle attributes
    player.width = 25;                                // Set the width of the player's paddle to 25 units
    player.height = 120;                              // Set the height of the player's paddle to 120 units
    player.x = screen_width - player.width - 10;      // Position the player's paddle near the right edge of the screen
    player.y = screen_height / 2 - player.height / 2; // Center the player's paddle vertically
    player.speed = 6;                                 // Set the player's paddle speed to 6 units per frame

    // Initialize CPU Paddle attributes
    cpu.width = 25;                             // Set the width of the CPU's paddle to 25 units
    cpu.height = 120;                           // Set the height of the CPU's paddle to 120 units
    cpu.x = 10;                                 // Position the CPU's paddle near the left edge of the screen
    cpu.y = screen_height / 2 - cpu.height / 2; // Center the CPU's paddle vertically
    cpu.speed = 6;                              // Set the CPU's paddle speed to 6 units per frame

    // Main game loop; continues until the window is closed
    while (WindowShouldClose() == false)
    {
        // Begin the drawing phase
        BeginDrawing();

        // Ball movement, just updating ball position
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Check for collision between the ball and the player's paddle
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1; // Reverse the ball's horizontal direction upon collision with player's paddle
        }

        // Check for collision between the ball and the CPU's paddle
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1; // Reverse the ball's horizontal direction upon collision with CPU's paddle
        }

        // Clearing Background
        ClearBackground(BLACK);

        // Drawing circle
        ball.Draw();

        // Drwaing Rectangle
        cpu.Draw();
        player.Draw();

        // Draw Court Line
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        // End the drawing phase
        EndDrawing();
    }

    // Close the window and free up resources
    CloseWindow();

    // Return 0 to indicate successful execution
    return 0;
}
