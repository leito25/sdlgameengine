/**
 * @file Game.h
 * @brief Core game engine class definition
 * @author TwoDEngine Development Team
 * @version 1.0
 * @date 2026-05-06
 *
 * This file contains the main Game class which manages the entire game lifecycle
 * including initialization, the game loop, input processing, updates, rendering,
 * and cleanup.
 */

#pragma once

/**
 * @class Game
 * @brief Main game engine class that manages the game lifecycle
 *
 * The Game class encapsulates all core game functionality including:
 * - SDL initialization and window management
 * - Main game loop execution
 * - Input event processing
 * - Game state updates
 * - Frame rendering
 * - Resource cleanup
 *
 * @section usage Usage Example
 * @code
 * int main(int argc, char* argv[])
 * {
 *     Game game;
 *     game.Initialize();
 *     game.Run();
 *     game.Destroy();
 *     return 0;
 * }
 * @endcode
 *
 * @note This class follows the game loop pattern with distinct phases:
 *       Input → Update → Render
 */
class Game
{
public:
    /**
     * @brief Default constructor
     *
     * Constructs a new Game object and initializes member variables to their
     * default states. Does not perform SDL initialization - call Initialize()
     * for that.
     *
     * @see Initialize()
     */
    Game();

    /**
     * @brief Destructor
     *
     * Destroys the Game object and ensures all resources are properly cleaned up.
     * If Destroy() has not been called, it will be called automatically.
     *
     * @see Destroy()
     */
    ~Game();

    /**
     * @brief Initialize the game engine and all subsystems
     *
     * Performs the following initialization steps:
     * - Initializes SDL and its extensions (SDL_image, SDL_ttf, SDL_mixer)
     * - Creates the game window
     * - Creates the hardware-accelerated renderer
     * - Initializes ImGui for debug UI
     * - Loads initial game assets
     * - Sets up the initial game state
     *
     * @return void (Consider changing to bool for error handling)
     *
     * @note Must be called before Run()
     * @warning Calling this multiple times without calling Destroy() first
     *          may cause resource leaks
     *
     * @see Destroy()
     *
     * @todo Change return type to bool to indicate success/failure
     * @todo Add error logging for initialization failures
     */
    void Initialize();

    /**
     * @brief Execute the main game loop
     *
     * Runs the game loop until the user quits. Each iteration of the loop:
     * 1. Calculates delta time since last frame
     * 2. Processes input events via ProcessInput()
     * 3. Updates game state via Update()
     * 4. Renders the frame via Render()
     * 5. Limits frame rate to target FPS
     *
     * The loop continues until a quit event is received (e.g., window close,
     * ESC key, or programmatic quit request).
     *
     * @note This is a blocking call that returns only when the game exits
     * @note Frame rate is typically capped at 60 FPS
     *
     * @see ProcessInput()
     * @see Update()
     * @see Render()
     */
    void Run();

    /**
     * @brief Process all input events from the user
     *
     * Polls and handles SDL events including:
     * - Keyboard input (key press/release)
     * - Mouse input (button press/release, motion, wheel)
     * - Window events (close, resize, focus)
     * - Game controller input
     *
     * This method is called once per frame by Run() and updates the internal
     * input state that can be queried during Update().
     *
     * @note ImGui events are processed first to allow UI interaction
     * @note Input state is accumulated and can be queried in Update()
     *
     * @see Run()
     * @see Update()
     */
    void ProcessInput();

    /**
     * @brief Update the game state based on elapsed time
     *
     * Updates all game logic including:
     * - Entity positions and velocities
     * - Animation states
     * - Collision detection and response
     * - AI behavior
     * - Physics simulation
     * - Script execution (Lua/Python)
     * - Audio playback
     *
     * All updates should be frame-rate independent by using delta time.
     *
     * @note Called once per frame by Run()
     * @note All movement and time-based changes should use delta time
     *
     * @see Run()
     * @see Render()
     *
     * @todo Add deltaTime parameter for frame-rate independence
     */
    void Update();

    /**
     * @brief Render the current game state to the screen
     *
     * Performs the following rendering steps:
     * 1. Clears the screen with background color
     * 2. Renders game background
     * 3. Renders all game entities (sprites, text, shapes)
     * 4. Renders UI elements
     * 5. Renders debug information (ImGui)
     * 6. Presents the final frame to the screen
     *
     * Rendering order is important for proper layering (back to front).
     *
     * @note Called once per frame by Run()
     * @note Uses double buffering - changes are not visible until SDL_RenderPresent()
     *
     * @see Run()
     * @see Update()
     */
    void Render();

    /**
     * @brief Clean up and destroy all game resources
     *
     * Performs cleanup in the following order:
     * 1. Destroys game-specific resources (textures, sounds, entities)
     * 2. Cleans up ImGui context
     * 3. Destroys SDL renderer
     * 4. Destroys SDL window
     * 5. Closes audio system
     * 6. Quits SDL extensions (TTF, IMG, Mixer)
     * 7. Quits SDL
     *
     * @note Should be called before the Game object is destroyed
     * @note Safe to call multiple times (subsequent calls are no-ops)
     * @warning Not calling this may cause resource leaks
     *
     * @see Initialize()
     */
    void Destroy();

private:
    // Window and rendering
    // TODO: Add SDL_Window* window;
    // TODO: Add SDL_Renderer* renderer;

    // Game State
    // TODO: Add bool isRunning;
    // TODO: Add bool isPaused;

    // Timing
    // TODO: Add Uint32 lastFrameTime;
    // TODO: Add float deltaTime;

    // Game Objects
    // TODO: Add std::vector<Entity*> entities;

    // Assets
    // TODO: Add std::map<std::string, SDL_Texture*> textures;
    // TODO: Add std::map<std::string, TTF_Font*> fonts;
    // TODO: Add std::map<std::string, Mix_Chunk*> sounds;

    // Scripting
    // TODO: Add sol::state luaState;
    // TODO: Add PythonBinding pythonBinding;
};
