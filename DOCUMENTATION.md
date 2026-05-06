# TwoDEngine - Class Documentation

This document provides detailed documentation for the classes and methods implemented in the TwoDEngine project.

---

## Table of Contents

1. [Overview](#overview)
2. [Game Class](#game-class)
   - [Constructor and Destructor](#constructor-and-destructor)
   - [Public Methods](#public-methods)
   - [Private Members](#private-members)
3. [Usage Examples](#usage-examples)
4. [Implementation Notes](#implementation-notes)

---

## Overview

TwoDEngine uses an object-oriented architecture with a main `Game` class that encapsulates all game functionality. This design follows the game loop pattern, separating concerns into initialization, input processing, state updates, rendering, and cleanup phases.

---

## Game Class

**File Location:** [`src/Game.h`](src/Game.h), [`src/Game.cpp`](src/Game.cpp)

The `Game` class is the core of the engine, managing the entire game lifecycle from initialization to cleanup.

### Class Declaration

```cpp
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
    // Window and rendering members
};
```

---

### Constructor and Destructor

#### `Game()`

**Description:** Default constructor for the Game class.

**Purpose:**
- Initializes the Game object
- Sets up initial state
- Prepares the game for initialization

**Parameters:** None

**Returns:** N/A (Constructor)

**Example:**
```cpp
Game game;  // Creates a new Game instance
```

**Implementation Details:**
- Currently outputs "Game constructor called" to console for debugging
- Does not perform SDL initialization (that's done in `Initialize()`)

---

#### `~Game()`

**Description:** Destructor for the Game class.

**Purpose:**
- Cleans up any resources allocated by the Game object
- Ensures proper cleanup when the Game object goes out of scope

**Parameters:** None

**Returns:** N/A (Destructor)

**Implementation Details:**
- Automatically called when the Game object is destroyed
- Should call `Destroy()` if not already called to ensure cleanup

---

### Public Methods

#### `void Initialize()`

**Description:** Initializes the game engine and all its subsystems.

**Purpose:**
- Sets up SDL and its extensions (SDL_image, SDL_ttf, SDL_mixer)
- Creates the game window
- Creates the renderer
- Initializes ImGui for debugging UI
- Loads initial assets
- Sets up the game state

**Parameters:** None

**Returns:** `void` (Note: Consider changing to `bool` to indicate success/failure)

**Usage:**
```cpp
Game game;
game.Initialize();
```

**Typical Implementation Steps:**
1. Initialize SDL with `SDL_Init(SDL_INIT_EVERYTHING)`
2. Initialize SDL extensions (IMG_Init, TTF_Init, Mix_OpenAudio)
3. Create window with `SDL_CreateWindow()`
4. Create renderer with `SDL_CreateRenderer()`
5. Initialize ImGui context
6. Load initial assets (textures, fonts, sounds)
7. Set up initial game state

**Error Handling:**
- Should check return values of all SDL functions
- Should use `SDL_GetError()` to retrieve error messages
- Should return false or throw exception on failure

---

#### `void Run()`

**Description:** Executes the main game loop.

**Purpose:**
- Runs the game until the user quits
- Coordinates the game loop phases: input → update → render
- Manages frame timing and frame rate

**Parameters:** None

**Returns:** `void`

**Usage:**
```cpp
Game game;
game.Initialize();
game.Run();  // Runs until user quits
game.Destroy();
```

**Typical Implementation:**
```cpp
void Game::Run()
{
    bool isRunning = true;

    while (isRunning)
    {
        // Calculate delta time
        float deltaTime = CalculateDeltaTime();

        // Process input
        ProcessInput();

        // Check if user wants to quit
        if (quitRequested)
            isRunning = false;

        // Update game state
        Update();

        // Render the frame
        Render();

        // Cap frame rate (optional)
        SDL_Delay(16);  // ~60 FPS
    }
}
```

---

#### `void ProcessInput()`

**Description:** Processes all input events from the user.

**Purpose:**
- Polls SDL events
- Handles keyboard input
- Handles mouse input
- Handles window events (close, resize, etc.)
- Updates input state for use in Update()

**Parameters:** None

**Returns:** `void`

**Usage:**
```cpp
// Called automatically by Run(), but can be called manually:
game.ProcessInput();
```

**Typical Implementation:**
```cpp
void Game::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        // Let ImGui handle its events first
        ImGui_ImplSDL2_ProcessEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quitRequested = true;
                break;

            case SDL_KEYDOWN:
                HandleKeyPress(event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                HandleKeyRelease(event.key.keysym.sym);
                break;

            case SDL_MOUSEBUTTONDOWN:
                HandleMouseClick(event.button);
                break;

            // ... other event types
        }
    }
}
```

**Events Handled:**
- `SDL_QUIT`: Window close button clicked
- `SDL_KEYDOWN`: Key pressed
- `SDL_KEYUP`: Key released
- `SDL_MOUSEBUTTONDOWN`: Mouse button pressed
- `SDL_MOUSEBUTTONUP`: Mouse button released
- `SDL_MOUSEMOTION`: Mouse moved
- `SDL_MOUSEWHEEL`: Mouse wheel scrolled
- `SDL_WINDOWEVENT`: Window events (resize, focus, etc.)

---

#### `void Update()`

**Description:** Updates the game state based on elapsed time.

**Purpose:**
- Updates game logic
- Moves entities
- Checks collisions
- Updates animations
- Processes AI
- Updates physics
- Executes game scripts (Lua/Python)

**Parameters:** None (Note: Consider adding `float deltaTime` parameter)

**Returns:** `void`

**Usage:**
```cpp
// Called automatically by Run(), but can be called manually:
game.Update();
```

**Typical Implementation:**
```cpp
void Game::Update()
{
    // Calculate delta time
    float deltaTime = GetDeltaTime();

    // Update player
    player.Update(deltaTime);

    // Update enemies
    for (auto& enemy : enemies)
    {
        enemy.Update(deltaTime);
    }

    // Check collisions
    CheckCollisions();

    // Update animations
    animationSystem.Update(deltaTime);

    // Update physics
    physicsWorld.Step(deltaTime);

    // Execute game scripts
    luaState["update"](deltaTime);
}
```

**Best Practices:**
- Use delta time for frame-rate independent movement
- Update in a consistent order to avoid race conditions
- Separate update logic from rendering logic

---

#### `void Render()`

**Description:** Renders the current game state to the screen.

**Purpose:**
- Clears the screen
- Renders game objects (sprites, text, shapes)
- Renders UI elements
- Renders debug information (ImGui)
- Presents the final frame to the screen

**Parameters:** None

**Returns:** `void`

**Usage:**
```cpp
// Called automatically by Run(), but can be called manually:
game.Render();
```

**Typical Implementation:**
```cpp
void Game::Render()
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game background
    RenderBackground();

    // Render game objects
    for (auto& entity : entities)
    {
        entity.Render(renderer);
    }

    // Render UI
    RenderUI();

    // Start ImGui frame
    ImGui::NewFrame();

    // Render ImGui debug windows
    RenderDebugUI();

    // Render ImGui
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    // Present the frame
    SDL_RenderPresent(renderer);
}
```

**Rendering Order:**
1. Clear screen
2. Render background
3. Render game objects (back to front)
4. Render UI elements
5. Render debug overlays (ImGui)
6. Present frame

---

#### `void Destroy()`

**Description:** Cleans up and destroys all game resources.

**Purpose:**
- Destroys SDL resources (textures, renderer, window)
- Cleans up ImGui
- Closes audio system
- Quits SDL subsystems
- Frees all allocated memory

**Parameters:** None

**Returns:** `void`

**Usage:**
```cpp
Game game;
game.Initialize();
game.Run();
game.Destroy();  // Clean up before exit
```

**Typical Implementation:**
```cpp
void Game::Destroy()
{
    // Destroy textures
    for (auto& texture : textures)
    {
        SDL_DestroyTexture(texture);
    }

    // Clean up ImGui
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();

    // Destroy renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Close audio
    Mix_CloseAudio();

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
```

**Cleanup Order:**
1. Destroy game-specific resources (textures, sounds, etc.)
2. Clean up ImGui
3. Destroy renderer
4. Destroy window
5. Close audio system
6. Quit SDL extensions (TTF, IMG, Mixer)
7. Quit SDL

---

### Private Members

The `Game` class should contain private member variables to store the game state. Typical members include:

```cpp
private:
    // SDL Components
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Game State
    bool isRunning;
    bool isPaused;

    // Timing
    Uint32 lastFrameTime;
    float deltaTime;

    // Game Objects
    std::vector<Entity*> entities;
    Player* player;

    // Assets
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, Mix_Music*> music;

    // Scripting
    sol::state luaState;
    PythonBinding pythonBinding;
```

---

## Usage Examples

### Basic Game Setup

```cpp
#include "Game.h"

int main(int argc, char* argv[])
{
    // Create game instance
    Game game;

    // Initialize the game
    game.Initialize();

    // Run the game loop
    game.Run();

    // Clean up
    game.Destroy();

    return 0;
}
```

### With Error Handling

```cpp
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        Game game;

        if (!game.Initialize())
        {
            std::cerr << "Failed to initialize game!" << std::endl;
            return 1;
        }

        game.Run();
        game.Destroy();

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}
```

---

## Implementation Notes

### Current Status

The `Game` class is currently in a **skeleton/stub** state:
- ✅ Class structure defined
- ✅ Method signatures declared
- ✅ Constructor implemented (basic)
- ⚠️ Methods are stubs (not fully implemented)
- ❌ Private members not yet defined
- ❌ SDL integration not yet implemented

### Next Steps for Implementation

1. **Add Private Members**
   - Add SDL_Window* and SDL_Renderer* members
   - Add game state flags (isRunning, isPaused)
   - Add timing variables (deltaTime, lastFrameTime)

2. **Implement Initialize()**
   - Initialize SDL and extensions
   - Create window and renderer
   - Set up ImGui
   - Return success/failure status

3. **Implement Run()**
   - Create main game loop
   - Calculate delta time
   - Call ProcessInput(), Update(), Render() in sequence
   - Handle frame rate limiting

4. **Implement ProcessInput()**
   - Poll SDL events
   - Handle keyboard/mouse input
   - Handle window events
   - Set quit flag when needed

5. **Implement Update()**
   - Add delta time parameter
   - Update game logic
   - Update entities
   - Check collisions

6. **Implement Render()**
   - Clear screen
   - Render game objects
   - Render ImGui
   - Present frame

7. **Implement Destroy()**
   - Clean up all resources
   - Destroy SDL objects
   - Quit SDL subsystems

### Design Considerations

1. **Error Handling**
   - Consider changing `Initialize()` to return `bool` for success/failure
   - Add error logging system
   - Use exceptions for critical errors

2. **Delta Time**
   - Add `deltaTime` parameter to `Update()` method
   - Calculate delta time in `Run()` method
   - Use high-resolution timer for accuracy

3. **Resource Management**
   - Consider using smart pointers for automatic cleanup
   - Implement resource manager for textures, sounds, etc.
   - Use RAII pattern for SDL resources

4. **Extensibility**
   - Consider making methods virtual for inheritance
   - Add hooks for custom game logic
   - Support plugin system

5. **Performance**
   - Profile rendering and update loops
   - Implement spatial partitioning for collision detection
   - Use object pooling for frequently created/destroyed objects

---

## Additional Classes (To Be Implemented)

Future documentation will cover:

- **Entity Class**: Base class for game objects
- **Player Class**: Player character implementation
- **Enemy Class**: Enemy AI and behavior
- **AssetManager Class**: Resource loading and management
- **CollisionSystem Class**: Collision detection and response
- **AnimationSystem Class**: Sprite animation management
- **AudioManager Class**: Sound and music management
- **ScriptManager Class**: Lua/Python script execution

---

**Last Updated:** 2026-05-06
**Version:** 1.0
**Author:** TwoDEngine Development Team
