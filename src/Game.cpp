#include "Game.h"
#include "Logger.h"
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

using namespace std;

Game::Game()
{
    // Constructor implementation
    Logger::Initialize();
    Logger::Info("Game constructor called");
}

Game::~Game()
{
    // Destructor implementation
    if (Logger::IsInitialized())
    {
        Logger::Info("Game destructor called");
    }
}

void Game::Initialize()
{
    // Initialize SDL, create window and renderer, load assets
    // Return true if initialization is successful

    //Initialize the SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Error(std::string("SDL_Init Error: ") + SDL_GetError());
        return;
    };

    // This is a pointer to a struct
    // which means that we need to dereference
    // it to access the members of the struct
    // this is usually used when we want to create
    // a new instance of a struct
    // why sdl use a struct pointer instead of a class is because
    // sdl is a c library and c does not have classes, it only has structs
    window = SDL_CreateWindow(
        "TwoD Game Enine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        //SDL_WINDOW_FULLSCREEN
        SDL_WINDOW_SHOWN
    );

    // Check if the window was created successfully
    if (window == nullptr)
    {
        Logger::Error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
        SDL_Quit();
        return;
    };

    // Create a renderer for the window
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE
    );

    // Check if the renderer was created successfully
    if (renderer == nullptr)
    {
        Logger::Error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
        //SDL_DestroyWindow(window);
        //SDL_Quit();
        return;
    };

    Logger::Info("Game initialized successfully");
    isRunning = true;
}

void Game::ProcessInput()
{
    // Handle keyboard and mouse input events
    SDL_Event sdlEvent; //Pure C struct, no constructor, so we need to declare it like this

    //passing the sdl as reference sended by reference to the function, so we can access the members of the struct
    // while to process all the evets in the queue,
    // we need to call SDL_PollEvent in a loop until it returns 0,
    // which means that there are no more events to process
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            // Handle quit event (e.g., window close)
            // sena message to the game loop to exit
            Logger::Info("SDL quit event received");
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // Handle key press event for quit with ESC key
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                Logger::Info("Escape key pressed; stopping game loop");
                isRunning = false;
            }
            break;

        default:
            break;
        }
    }
    SDL_PollEvent(&sdlEvent);
}




void Game::Run()
{
    //Calling the Setup as a initialization of the variables
    Setup();
    Logger::Info("Game loop started");

    // Main game loop: process input, update game state, render frames
    // Clean up resources, destroy window and renderer,
    // quit SDL
    while(isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }

    Logger::Info("Game loop stopped");
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup()
{
    // TODO Initialize Game Objects
    // This setup methods is like the Start of Unity
    // Or the Begin of Unreal Engine

    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(1.0, 0.0);
    Logger::Info("Game::Setup completed");
}
int c = 0;
void Game::Update()
{
    // Same delay using SDL TICKS PASSED but this time
    // using SDL Delay
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    // Update game state based on elapsed time
    playerPosition.x += playerVelocity.x;
    playerPosition.y += playerVelocity.y;


    // This all process is manual but implies a really waste of resources
    // A better option is to use SDL_Delay

    // add a delay until the frame time ends
    // SDL TICKS PASSED (current tick, last tick
    /*Logger::Debug("Before millisecsPreviousFrame: " + std::to_string(millisecsPreviousFrame));
    Logger::Debug("Before MILLISECS_PER_FRAME: " + std::to_string(MILLISECS_PER_FRAME));
    Logger::Debug("Before SDL_GetTicks(): " + std::to_string(SDL_GetTicks()));
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), millisecsPreviousFrame + MILLISECS_PER_FRAME))
    {
        Logger::Debug("Real Time Tick: " + std::to_string(SDL_GetTicks()));
    }

    // store the current frame
    millisecsPreviousFrame = SDL_GetTicks();

    Logger::Debug("After millisecsPreviousFrame: " + std::to_string(millisecsPreviousFrame));
    Logger::Debug("After MILLISECS_PER_FRAME: " + std::to_string(MILLISECS_PER_FRAME));
    Logger::Debug("After SDL_GetTicks(): " + std::to_string(SDL_GetTicks()));
    */
}

void Game::Render()
{
    // Render the game scene

    /// First test is paint hte windows with a simple color navy blue
    // Set the draw color to navy blue (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    // Clear the renderer is done for us by the SDL_RenderClear function,
    // which will fill the entire rendering target with the drawing color
    // why is this necesary? because we need to clear the previous frame
    // before we can render the new frame, otherwise we will have a mess of frames on the screen
    SDL_RenderClear(renderer);

    // Over this code a SDL rectangle will be created
    //SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // apply color to the new REct
    //SDL_Rect player = {15, 15, 200, 50};
    //SDL_RenderFillRect(renderer, &player);

    // Draw a PNG Texture
    // SDL core only read bitmap files
    // so it would be necessary to use the texture library
    //...
    // SDL Surface method get the path and create a surface
    SDL_Surface* surface = IMG_Load("./assets/images/tank-panther-right.png");
    if (surface == nullptr)
    {
        Logger::Error(std::string("IMG_Load Error: ") + IMG_GetError());
        return;
    }

    // SDL Texture create a texture pointer based on the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    //Finally the surface already created is freed
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        Logger::Error(std::string("SDL_CreateTextureFromSurface Error: ") + SDL_GetError());
        return;
    }

    // Now for use the texture in a Rect
    // A rect needs to be created
    //the width and heigth are the same as the texture
    //SDL_Rect dstRect = {50, 50, 32, 32};

    Logger::Debug("Player position: " + std::to_string(playerPosition.x) + ", " + std::to_string(playerPosition.y));

    //Now I'll replace the rect position with the position updated in the game
    SDL_Rect dstRect = {
        static_cast<int>(playerPosition.x),
        static_cast<int>(playerPosition.y),
        32,
        32
    };



    // A copy should be made, in shaders is like a blit
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);//NULL for the entire texture
    // Destroy the texture to avoid waste memory
    SDL_DestroyTexture(texture);




    // Present the rendered frame to the screen
    // why do we need to call this function?
    // because SDL uses double buffering,
    //which means that we have two buffers,
    // one for rendering and one for presenting,
    // and we need to call this function to swap the
    // buffers and present the rendered frame to the screen
    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    // Clean up resources, destroy window and renderer, quit SDL

    // Free all the resource allocated
    //The order is importatnt because
    // we need to destroy the renderer
    // before the window
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
    Logger::Info("Game resources destroyed");
    Logger::Shutdown();
}
