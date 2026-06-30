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

#include <SDL.h>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000/FPS;

/**
 * @class Game
 * @brief Main game engine class that manages the game lifecycle
 *
 * The Game class encapsulates all core game functionality including:
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
    Game();
    ~Game();

    void Initialize();

    void Run();

    void ProcessInput();

    void LoadLevel(int level);

    void Setup();

    void Update();

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
    bool isRunning = false; // Flag to control the main game loop
    int millisecsPreviousFrame = 0;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    //Registry* registry; // ECS registry to manage entities and systems
    // now using a smat pointer for the registry
    std::unique_ptr<Registry> registry;
    // Asset Store manager
    std::unique_ptr<AssetStore> assetStore;

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
