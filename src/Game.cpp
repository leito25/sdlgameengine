#include "Game.h"
#include <iostream>
#include <SDL.h>

using namespace std;

Game::Game()
{
    // Constructor implementation
    cout << "Game constructor called" << std::endl;
}

Game::~Game()
{
    // Destructor implementation
    cout << "Game destructor called" << std::endl;
}

void Game::Initialize()
{
    // Initialize SDL, create window and renderer, load assets
    // Return true if initialization is successful

    //Initialize the SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return;
    };

    // This is a pointer to a struct
    // wich means that we need to dereference
    // it to access the members of the struct
    // this is ussually used when we want to create
    // a new instance of a struct
    // why sdl use a struct pointer instead of a class is because
    // sdl is a c library and c does not have classes, it only has structs
    window = SDL_CreateWindow(
        "TwoD Game Enine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_SHOWN
    );

    // Check if the window was created successfully
    if (window == nullptr)
    {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
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
        cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        //SDL_DestroyWindow(window);
        //SDL_Quit();
        return;
    };

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
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // Handle key press event for quit with ESC key
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
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
    // Main game loop: process input, update game state, render frames
    // Clean up resources, destroy window and renderer,
    // quit SDL
    while(isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Update()
{
    // Update game state based on elapsed time
}

void Game::Render()
{
    // Render the game scene

    /// First test is paint hte windows with a simple color navy blue
    // Set the draw color to navy blue (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);
    // Clear the renderer is done for us by the SDL_RenderClear function,
    // which will fill the entire rendering target with the drawing color
    // why is this necesary? because we need to clear the previous frame
    // before we can render the new frame, otherwise we will have a mess of frames on the screen
    SDL_RenderClear(renderer);

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

