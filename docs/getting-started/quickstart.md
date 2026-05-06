# Quick Start Guide

This guide will help you get TwoDEngine up and running in just a few minutes.

## Prerequisites

Before you begin, ensure you have the following installed:

- **Git**: For cloning the repository
- **MinGW-w64** (Windows) or **GCC** (Linux/macOS): C++ compiler
- **Make**: Build automation tool

## Installation

### Step 1: Clone the Repository

```bash
git clone https://github.com/yourusername/TwoDEngine.git
cd TwoDEngine
```

### Step 2: Run Setup Script

TwoDEngine includes a convenient setup script that downloads and configures all dependencies.

#### Windows
```cmd
setup.bat
```

#### Linux/macOS
```bash
chmod +x setup.sh
./setup.sh
```

The setup script will:

- Download SDL2 and related libraries
- Download Lua 5.4
- Download Python 3.10 (if needed)
- Download pybind11
- Configure all dependencies
- Verify the installation

!!! success "Setup Complete"
    If the setup completes successfully, you'll see a message indicating all dependencies are ready.

## Building the Engine

### Using Make

The simplest way to build TwoDEngine is using the provided Makefile:

```bash
# Build the engine
make

# Clean build artifacts
make clean

# Rebuild from scratch
make clean && make
```

### Using Batch Files (Windows)

TwoDEngine provides convenient batch files for common tasks:

```cmd
# Build and run the engine
build_and_run.bat

# Build, run, and package the engine
build_run_engine.bat
```

## Your First Program

Let's create a simple program that initializes the game engine.

### 1. Create Main.cpp

Create a file `src/Main.cpp` with the following content:

```cpp
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Starting TwoDEngine..." << std::endl;

    // Create game instance
    Game game;

    // Initialize the engine
    game.Initialize();

    // Run the game loop
    game.Run();

    // Clean up resources
    game.Destroy();

    std::cout << "TwoDEngine shutdown complete." << std::endl;

    return 0;
}
```

### 2. Create Game.h

Create a file `src/Game.h`:

```cpp
#ifndef GAME_H
#define GAME_H

/**
 * @class Game
 * @brief Main game engine class
 */
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
    bool isRunning;
};

#endif // GAME_H
```

### 3. Create Game.cpp

Create a file `src/Game.cpp`:

```cpp
#include "Game.h"
#include <iostream>

Game::Game() : isRunning(false)
{
    std::cout << "Game constructor called" << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called" << std::endl;
}

void Game::Initialize()
{
    std::cout << "Initializing game..." << std::endl;
    isRunning = true;
}

void Game::Run()
{
    std::cout << "Starting game loop..." << std::endl;

    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();

        // For now, exit after one iteration
        isRunning = false;
    }
}

void Game::ProcessInput()
{
    // TODO: Handle input
}

void Game::Update()
{
    // TODO: Update game logic
}

void Game::Render()
{
    // TODO: Render graphics
}

void Game::Destroy()
{
    std::cout << "Cleaning up resources..." << std::endl;
}
```

### 4. Build and Run

```bash
# Build the project
make

# Run the executable
./bin/main.exe  # Windows
./bin/main      # Linux/macOS
```

You should see output similar to:

```
Starting TwoDEngine...
Game constructor called
Initializing game...
Starting game loop...
Cleaning up resources...
Game destructor called
TwoDEngine shutdown complete.
```

## Next Steps

Congratulations! You've successfully set up TwoDEngine and created your first program. Here's what to explore next:

<div class="grid cards" markdown>

-   :material-window-maximize:{ .lg .middle } __Creating a Window__

    ---

    Learn how to create an SDL window and renderer

    [:octicons-arrow-right-24: Window Creation](../user-guide/window.md)

-   :material-gamepad-variant:{ .lg .middle } __Handling Input__

    ---

    Process keyboard, mouse, and controller input

    [:octicons-arrow-right-24: Input Handling](../user-guide/input.md)

-   :material-image:{ .lg .middle } __Loading Assets__

    ---

    Load and display images, fonts, and sounds

    [:octicons-arrow-right-24: Asset Management](../user-guide/assets.md)

-   :material-script-text:{ .lg .middle } __Using Lua Scripts__

    ---

    Add scripting capabilities to your game

    [:octicons-arrow-right-24: Lua Scripting](../user-guide/lua-scripting.md)

</div>

## Troubleshooting

### Build Errors

If you encounter build errors, try:

1. **Clean and rebuild**: `make clean && make`
2. **Verify dependencies**: Run `setup.bat` again
3. **Check compiler**: Ensure MinGW or GCC is in your PATH

### Missing DLLs (Windows)

If you get "missing DLL" errors when running:

1. Ensure all DLLs are in the `bin/` directory
2. Run `setup.bat` to copy DLLs automatically
3. Check that SDL2, Lua, and Python DLLs are present

### Linker Errors

If you get undefined reference errors:

1. Verify all `.cpp` files are listed in the Makefile
2. Check that library paths are correct
3. Ensure all required libraries are linked

## Getting Help

If you're stuck, here are some resources:

- **Documentation**: Browse the [User Guide](../user-guide/overview.md)
- **API Reference**: Check the [API Documentation](../api/overview.md)
- **Examples**: Look at [Example Projects](../examples/basic-game.md)
- **GitHub Issues**: Search or create an issue on GitHub

---

!!! tip "Pro Tip"
    Use the provided batch files (`build_and_run.bat`, `build_run_engine.bat`) for faster development iterations on Windows!
