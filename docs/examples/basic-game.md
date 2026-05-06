# Basic Game Example

This example demonstrates how to create a simple game with TwoDEngine, including window creation, input handling, and basic rendering.

## Overview

We'll create a simple game where a player-controlled square moves around the screen using keyboard input.

## Complete Code

### Main.cpp

```cpp
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Starting Simple Game..." << std::endl;

    try {
        Game game;
        game.Initialize();
        game.Run();
        game.Destroy();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Game exited successfully." << std::endl;
    return 0;
}
```

### Game.h

```cpp
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game();

    void Initialize();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    // Player properties
    SDL_Rect player;
    int playerSpeed;

    // Input state
    bool moveUp;
    bool moveDown;
    bool moveLeft;
    bool moveRight;
};

#endif // GAME_H
```

### Game.cpp

```cpp
#include "Game.h"
#include <iostream>

Game::Game()
    : window(nullptr)
    , renderer(nullptr)
    , isRunning(false)
    , playerSpeed(200)
    , moveUp(false)
    , moveDown(false)
    , moveLeft(false)
    , moveRight(false)
{
    // Initialize player position and size
    player.x = 400;
    player.y = 300;
    player.w = 50;
    player.h = 50;
}

Game::~Game()
{
    Destroy();
}

void Game::Initialize()
{
    std::cout << "Initializing SDL..." << std::endl;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("SDL initialization failed: " + std::string(SDL_GetError()));
    }

    // Create window
    window = SDL_CreateWindow(
        "TwoDEngine - Basic Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        throw std::runtime_error("Window creation failed: " + std::string(SDL_GetError()));
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        throw std::runtime_error("Renderer creation failed: " + std::string(SDL_GetError()));
    }

    isRunning = true;
    std::cout << "Initialization complete!" << std::endl;
}

void Game::Run()
{
    std::cout << "Starting game loop..." << std::endl;

    Uint32 lastFrameTime = SDL_GetTicks();

    while (isRunning)
    {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentTime;

        // Cap delta time to prevent large jumps
        if (deltaTime > 0.05f)
            deltaTime = 0.05f;

        ProcessInput();
        Update(deltaTime);
        Render();
    }

    std::cout << "Game loop ended." << std::endl;
}

void Game::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    case SDLK_w:
                    case SDLK_UP:
                        moveUp = true;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        moveDown = true;
                        break;
                    case SDLK_a:
                    case SDLK_LEFT:
                        moveLeft = true;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        moveRight = true;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_UP:
                        moveUp = false;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        moveDown = false;
                        break;
                    case SDLK_a:
                    case SDLK_LEFT:
                        moveLeft = false;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        moveRight = false;
                        break;
                }
                break;
        }
    }
}

void Game::Update(float deltaTime)
{
    // Update player position based on input
    if (moveUp)
        player.y -= static_cast<int>(playerSpeed * deltaTime);
    if (moveDown)
        player.y += static_cast<int>(playerSpeed * deltaTime);
    if (moveLeft)
        player.x -= static_cast<int>(playerSpeed * deltaTime);
    if (moveRight)
        player.x += static_cast<int>(playerSpeed * deltaTime);

    // Keep player within screen bounds
    if (player.x < 0) player.x = 0;
    if (player.y < 0) player.y = 0;
    if (player.x + player.w > 800) player.x = 800 - player.w;
    if (player.y + player.h > 600) player.y = 600 - player.h;
}

void Game::Render()
{
    // Clear screen (dark blue background)
    SDL_SetRenderDrawColor(renderer, 20, 30, 50, 255);
    SDL_RenderClear(renderer);

    // Draw player (white square)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &player);

    // Present frame
    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    std::cout << "Cleaning up resources..." << std::endl;

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();

    std::cout << "Cleanup complete." << std::endl;
}
```

## Building and Running

### Compile the Game

```bash
# Build using Make
make

# Or use the batch file (Windows)
build_and_run.bat
```

### Run the Game

```bash
# Windows
bin\main.exe

# Linux/macOS
./bin/main
```

## Controls

- **Arrow Keys** or **WASD**: Move the player
- **ESC**: Exit the game
- **Close Window**: Exit the game

## How It Works

### 1. Initialization

```cpp
void Game::Initialize()
{
    // Initialize SDL video subsystem
    SDL_Init(SDL_INIT_VIDEO);

    // Create 800x600 window
    window = SDL_CreateWindow(...);

    // Create hardware-accelerated renderer with VSync
    renderer = SDL_CreateRenderer(...);
}
```

### 2. Game Loop

```cpp
void Game::Run()
{
    while (isRunning)
    {
        // Calculate time since last frame
        float deltaTime = CalculateDeltaTime();

        // Process input, update, render
        ProcessInput();
        Update(deltaTime);
        Render();
    }
}
```

### 3. Input Handling

```cpp
void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle keyboard events
        if (event.type == SDL_KEYDOWN)
        {
            // Set movement flags
            if (event.key.keysym.sym == SDLK_w)
                moveUp = true;
        }
    }
}
```

### 4. Update Logic

```cpp
void Game::Update(float deltaTime)
{
    // Move player based on input
    if (moveUp)
        player.y -= playerSpeed * deltaTime;

    // Keep player in bounds
    if (player.x < 0) player.x = 0;
}
```

### 5. Rendering

```cpp
void Game::Render()
{
    // Clear screen
    SDL_RenderClear(renderer);

    // Draw player
    SDL_RenderFillRect(renderer, &player);

    // Present frame
    SDL_RenderPresent(renderer);
}
```

## Enhancements

Try adding these features to improve the game:

### Add a Background Color

```cpp
void Game::Render()
{
    // Set background color (RGB)
    SDL_SetRenderDrawColor(renderer, 50, 100, 150, 255);
    SDL_RenderClear(renderer);

    // ... rest of rendering
}
```

### Add Player Color

```cpp
void Game::Render()
{
    // Draw player in green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &player);
}
```

### Add Diagonal Movement

```cpp
void Game::Update(float deltaTime)
{
    float moveX = 0.0f;
    float moveY = 0.0f;

    if (moveUp) moveY -= 1.0f;
    if (moveDown) moveY += 1.0f;
    if (moveLeft) moveX -= 1.0f;
    if (moveRight) moveX += 1.0f;

    // Normalize diagonal movement
    if (moveX != 0.0f && moveY != 0.0f)
    {
        float length = sqrt(moveX * moveX + moveY * moveY);
        moveX /= length;
        moveY /= length;
    }

    player.x += static_cast<int>(moveX * playerSpeed * deltaTime);
    player.y += static_cast<int>(moveY * playerSpeed * deltaTime);
}
```

### Add Frame Rate Display

```cpp
void Game::Render()
{
    // ... existing rendering code

    // Calculate FPS
    static int frameCount = 0;
    static Uint32 lastTime = SDL_GetTicks();
    frameCount++;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastTime >= 1000)
    {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        lastTime = currentTime;
    }
}
```

## Next Steps

Now that you have a basic game running, try these tutorials:

- [Loading Images](sprite-rendering.md): Display sprites instead of rectangles
- [Adding Sound](audio-example.md): Add sound effects and music
- [Multiple Objects](entity-management.md): Create multiple game objects
- [Collision Detection](collision-example.md): Detect when objects collide

---

!!! success "Congratulations!"
    You've created your first game with TwoDEngine! This example demonstrates the core concepts you'll use in all your games.
