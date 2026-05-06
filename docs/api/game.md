# Game Class

The `Game` class is the core of TwoDEngine, managing the entire game lifecycle from initialization to shutdown.

## Overview

The `Game` class implements the main game loop pattern and coordinates all engine subsystems. It provides a simple interface for creating games while handling complex initialization and management tasks behind the scenes.

## Class Declaration

```cpp
/**
 * @file Game.h
 * @brief Core game engine class definition
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
    // Private implementation details
};
```

## Constructor

### `Game()`

```cpp
Game();
```

**Description**: Constructs a new Game instance.

**Parameters**: None

**Example**:
```cpp
Game game;  // Create game instance
```

**Notes**:
- The constructor performs minimal initialization
- Heavy initialization is deferred to `Initialize()`
- Safe to create multiple Game instances (though typically only one is needed)

## Destructor

### `~Game()`

```cpp
~Game();
```

**Description**: Destroys the Game instance and releases resources.

**Parameters**: None

**Example**:
```cpp
{
    Game game;
    // Game is automatically destroyed when going out of scope
}
```

**Notes**:
- Automatically calls cleanup code
- Ensures proper resource deallocation
- Safe to call even if `Initialize()` was never called

## Public Methods

### `Initialize()`

```cpp
void Initialize();
```

**Description**: Initializes all game engine subsystems.

This method sets up:
- SDL2 video and audio systems
- Window and rendering context
- Asset management system
- Input handling system
- Scripting engines (Lua and Python)

**Parameters**: None

**Returns**: void

**Throws**: May throw exceptions if initialization fails

**Example**:
```cpp
Game game;
game.Initialize();
```

**Best Practices**:
```cpp
Game game;
try {
    game.Initialize();
    game.Run();
} catch (const std::exception& e) {
    std::cerr << "Initialization failed: " << e.what() << std::endl;
    return 1;
}
game.Destroy();
```

**Notes**:
- Must be called before `Run()`
- Should only be called once per Game instance
- Calling multiple times without `Destroy()` may cause resource leaks

**See Also**: [`Destroy()`](#destroy)

---

### `Run()`

```cpp
void Run();
```

**Description**: Starts the main game loop.

The game loop continuously:
1. Processes input events
2. Updates game logic
3. Renders the current frame
4. Maintains target frame rate

**Parameters**: None

**Returns**: void

**Example**:
```cpp
Game game;
game.Initialize();
game.Run();  // Blocks until game exits
game.Destroy();
```

**Game Loop Structure**:
```cpp
while (isRunning)
{
    ProcessInput();  // Handle user input
    Update();        // Update game state
    Render();        // Draw to screen

    // Frame rate limiting
    CapFrameRate();
}
```

**Notes**:
- This method blocks until the game exits
- The loop runs at the target frame rate (typically 60 FPS)
- Exit the loop by setting `isRunning = false`

**See Also**: [`ProcessInput()`](#processinput), [`Update()`](#update), [`Render()`](#render)

---

### `ProcessInput()`

```cpp
void ProcessInput();
```

**Description**: Processes all input events for the current frame.

Handles:
- Keyboard input
- Mouse input
- Controller input
- Window events (close, resize, etc.)

**Parameters**: None

**Returns**: void

**Example**:
```cpp
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
                HandleKeyPress(event.key.keysym.sym);
                break;
            // Handle other events...
        }
    }
}
```

**Typical Usage**:
```cpp
// In your game loop
while (isRunning)
{
    ProcessInput();  // Called first each frame
    Update();
    Render();
}
```

**Notes**:
- Called once per frame at the start of the game loop
- Processes all pending events in the SDL event queue
- Should be fast to avoid input lag

**See Also**: [`Run()`](#run)

---

### `Update()`

```cpp
void Update();
```

**Description**: Updates game logic for the current frame.

This method handles:
- Game state updates
- Physics simulation
- AI logic
- Animation updates
- Collision detection
- Script execution

**Parameters**: None

**Returns**: void

**Example**:
```cpp
void Game::Update()
{
    // Update delta time
    float deltaTime = CalculateDeltaTime();

    // Update game entities
    for (auto& entity : entities)
    {
        entity.Update(deltaTime);
    }

    // Update physics
    physicsWorld.Step(deltaTime);

    // Check collisions
    collisionSystem.CheckCollisions();
}
```

**Delta Time Pattern**:
```cpp
void Game::Update()
{
    // Calculate time since last frame
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;

    // Use deltaTime for frame-rate independent updates
    playerPosition += playerVelocity * deltaTime;
}
```

**Notes**:
- Called once per frame after `ProcessInput()`
- Should use delta time for frame-rate independent behavior
- Keep updates efficient to maintain target frame rate

**See Also**: [`Run()`](#run), [`Render()`](#render)

---

### `Render()`

```cpp
void Render();
```

**Description**: Renders the current frame to the screen.

This method:
1. Clears the screen
2. Renders all game objects
3. Renders UI elements
4. Presents the frame to the display

**Parameters**: None

**Returns**: void

**Example**:
```cpp
void Game::Render()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game objects
    for (auto& entity : entities)
    {
        entity.Render(renderer);
    }

    // Render UI
    RenderUI();

    // Present frame
    SDL_RenderPresent(renderer);
}
```

**Rendering Order**:
```cpp
void Game::Render()
{
    // 1. Clear screen
    ClearScreen();

    // 2. Render background
    RenderBackground();

    // 3. Render game world (sorted by depth)
    RenderGameWorld();

    // 4. Render particles/effects
    RenderEffects();

    // 5. Render UI (always on top)
    RenderUI();

    // 6. Present to screen
    PresentFrame();
}
```

**Notes**:
- Called once per frame after `Update()`
- Should only contain rendering code, no game logic
- Render order matters for proper layering

**See Also**: [`Run()`](#run), [`Update()`](#update)

---

### `Destroy()`

```cpp
void Destroy();
```

**Description**: Cleans up and releases all engine resources.

This method:
- Destroys all game entities
- Releases loaded assets
- Shuts down SDL subsystems
- Closes scripting engines
- Frees allocated memory

**Parameters**: None

**Returns**: void

**Example**:
```cpp
Game game;
game.Initialize();
game.Run();
game.Destroy();  // Clean up before exit
```

**Best Practice with RAII**:
```cpp
int main(int argc, char* argv[])
{
    try {
        Game game;
        game.Initialize();
        game.Run();
        game.Destroy();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

**Notes**:
- Should be called before program exit
- Safe to call multiple times
- Automatically called by destructor if not called explicitly

**See Also**: [`Initialize()`](#initialize)

## Complete Usage Example

### Basic Game

```cpp
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Starting TwoDEngine..." << std::endl;

    // Create game instance
    Game game;

    // Initialize engine
    game.Initialize();

    // Run game loop
    game.Run();

    // Clean up
    game.Destroy();

    std::cout << "Game exited successfully." << std::endl;
    return 0;
}
```

### With Error Handling

```cpp
#include "Game.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[])
{
    try {
        Game game;

        std::cout << "Initializing engine..." << std::endl;
        game.Initialize();

        std::cout << "Starting game..." << std::endl;
        game.Run();

        std::cout << "Shutting down..." << std::endl;
        game.Destroy();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
}
```

## Implementation Status

| Method | Status | Notes |
|--------|--------|-------|
| `Game()` | ✅ Implemented | Basic constructor |
| `~Game()` | ✅ Implemented | Basic destructor |
| `Initialize()` | 🚧 Stub | Needs SDL initialization |
| `Run()` | 🚧 Stub | Needs game loop implementation |
| `ProcessInput()` | 🚧 Stub | Needs input handling |
| `Update()` | 🚧 Stub | Needs game logic |
| `Render()` | 🚧 Stub | Needs rendering code |
| `Destroy()` | 🚧 Stub | Needs cleanup code |

## Design Patterns

The `Game` class implements several design patterns:

### Singleton Pattern (Optional)
```cpp
class Game
{
public:
    static Game& GetInstance()
    {
        static Game instance;
        return instance;
    }

private:
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};
```

### Game Loop Pattern
```cpp
void Game::Run()
{
    while (isRunning)
    {
        ProcessInput();  // Input phase
        Update();        // Update phase
        Render();        // Render phase
    }
}
```

## Performance Considerations

- **Frame Rate**: Target 60 FPS (16.67ms per frame)
- **Update Budget**: ~10ms for Update()
- **Render Budget**: ~6ms for Render()
- **Input Budget**: ~1ms for ProcessInput()

## Thread Safety

The `Game` class is **not thread-safe**. All methods should be called from the main thread only.

For multi-threaded operations:
- Use a separate thread for asset loading
- Use a separate thread for physics simulation
- Synchronize with the main thread using mutexes

## Future Enhancements

- [ ] Add configuration file support
- [ ] Implement scene management
- [ ] Add profiling and debugging tools
- [ ] Support for multiple windows
- [ ] Hot-reloading of assets and scripts

---

!!! info "Source Code"
    View the complete source code: [`src/Game.h`](../../src/Game.h) | [`src/Game.cpp`](../../src/Game.cpp)
