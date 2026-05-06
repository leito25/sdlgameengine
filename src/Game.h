#pragma once

class Game
{
public:
    Game();
    ~Game();

    /**
     * Initialize the game engine.
     * Sets up SDL, creates the window, renderer, and loads initial assets.
     * @return true if initialization was successful, false otherwise
     */
    void Initialize();

    /**
     * Run the main game loop.
     * Processes events, updates game state, and renders frames.
     */
    void Run();

    /**
     * Process input events such as keyboard and mouse input.
     * This is called every frame to handle user interactions.
     */
    void ProcessInput();

    /**
     * Update the game state based on the time elapsed since the last frame.
     * @param deltaTime Time in seconds since the last frame
     */
    void Update();

    /**
     * Render the game scene.
     * This is called every frame to display the game state.
     */
    void Render();

    /**
     * Clean up and destroy game resources.
     * Closes the window, destroys the renderer, and cleans up SDL.
     */
    void Destroy();
private:
    // Window and rendering

};
