# My Pong Game

## Overview

This project is a simple Pong game built using C++ and the Raylib library. The game features a player-controlled paddle and a CPU-controlled paddle trying to hit a bouncing ball.

## Features

- Player vs CPU gameplay
- Ball collision with paddles and walls
- Simple and clean UI

## Requirements

- C++ Compiler (e.g., g++, clang)
- [Raylib](https://www.raylib.com/) library

## Compilation and Running

To compile the project, navigate to the project directory and run the following command:

\`\`\`bash
g++ main.cpp -o MyPongGame -lraylib
\`\`\`

To run the game, execute the following command:

\`\`\`bash
./MyPongGame
\`\`\`

## Controls

- **Up Arrow**: Move player's paddle up
- **Down Arrow**: Move player's paddle down

## Classes

### Ball

- `Draw()`: Draws the ball on the screen
- `Update()`: Updates the ball's position and handles wall collisions

### Paddle

- `Draw()`: Draws the paddle on the screen
- `Update()`: Updates the paddle's position based on user input

### CpuPaddle (Inherits from Paddle)

- `Update(int ball_y)`: Updates the CPU paddle's position based on the ball's y-coordinate

## Future Enhancements

- Implementing different difficulty levels for the CPU
- Adding sound effects and background music
