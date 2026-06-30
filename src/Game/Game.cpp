#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include "../Logger/MyLogger.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../AssetStore/AssetStore.h"

using namespace std;

Game::Game()
{
    isRunning = false;

    // Initialize the registry for ECS
    //registry = new Registry();  // there is not a destructor for the registry, so we need to delete it in the destructor of the game

    // instead using the new operator,
    // we could use a smart pointer
    registry = std::make_unique<Registry>();

    // Pointer to manager
    assetStore = std::make_unique<AssetStore>();

    MyLogger::Log("Game constructor called!");
}

Game::~Game()
{
    MyLogger::Log("Game destructor called!");
}

void Game::Initialize()
{
    // Initialize SDL, create window and renderer, load assets
    // Return true if initialization is successful

    //Initialize the SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Error(std::string("SDL_Init Error: ") + SDL_GetError());
        MyLogger::Err(std::string("SDL_Init Error: ") + SDL_GetError());
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

    MyLogger::Log("Game initialized successfully");
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

void Game::LoadLevel(int level)
{
    MyLogger::Log("Loading Level 1");

    // Adding the System
    registry->AddSystem<MovementSystem>();
    // Adding a Render System
    registry->AddSystem<RenderSystem>();

    // Adding an image to the Assets manager
    assetStore->AddTexture(renderer, "tank-image", "assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "assets/images/truck-ford-right.png");

    //TODO:
    // Load the tilemap
    // Load the tilemap texture
    // Load the map file
    // Tip: idea source rectangle
    // Tip: one entity per tile

    //Solution
    //Addint the TExture tot he AssetStore
    assetStore->AddTexture(renderer, "tilemap-image", "assets/tilemaps/jungle.png");

    //Loading the tilemap
    int tileSize = 32;
    float tileScale = 2.0;
    int mapNumCols = 25;
    int mapNumRows = 20;

    //Open the map config file
    std::fstream mapFile;
    mapFile.open("assets/tilemaps/jungle.map");

    // for loop to create the tiles
    for (int y = 0; y < mapNumRows; y++)
    {
        for (int x = 0; x < mapNumCols; x++)
        {
            //TODO
            char ch;

            mapFile.get(ch);
            int srcRectY = std::atoi(&ch) * tileSize;

            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * tileSize;

            mapFile.ignore();

            Entity tile = registry->CreateEntity();
            tile.AddComponent<TransformComponent>(glm::vec2(x*(tileSize*tileScale), y*(tileSize*tileScale)), glm::vec2(tileScale, tileScale), 0.0);
            tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, srcRectX, srcRectY);
        }
    }

    mapFile.close();

    // Now here we go the setup code
    // Create some entities and add them to the registry
    Entity tank = registry->CreateEntity();
    Entity truck = registry->CreateEntity();


    // New Testing adding component directly from the entity
    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 30.0), glm::vec2(2.0, 2.0), 0.0);
    tank.AddComponent<RigidBodyComponent>(glm::vec2(50.0, 0.0));
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32);

    truck.AddComponent<TransformComponent>(glm::vec2(15.0, 0.0), glm::vec2(2.0, 2.0), 0.0);
    truck.AddComponent<RigidBodyComponent>(glm::vec2(5.0, 5.0));
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32);
}

void Game::Setup()
{
    LoadLevel(1);
    Logger::Info("Game::Setup completed");
}
//int c = 0;
void Game::Update()
{
    // Same delay using SDL TICKS PASSED but this time
    // using SDL Delay
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        //SDL_Delay(timeToWait);
    }

    // The difference in ticks (time ticks) since the last frame, convert to seconds
    // this is done to maintain a constance velocity no matter the specs of the machine
    // or the framerate
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    // Store the previous frame time that was use before in the
    // SDL TICKS PASSED ticks approach
    millisecsPreviousFrame = SDL_GetTicks();

    //int vel = 5;

    // Update game state based on elapsed time
    //playerPosition.x += playerVelocity.x * 50 * deltaTime;
    //playerPosition.y += playerVelocity.y * 50 * deltaTime;

    //TODO: Updating the REgistry manager (entities waiting to be created or deleted)
    registry->Update();

    //TODO: Updating the systems
    registry->GetSystem<MovementSystem>().Update(deltaTime);


}

void Game::Render()
{
    // Set the Renderer Base Color
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);

    // Clear
    SDL_RenderClear(renderer);

    // Runnning the Render System passing the renderer as argument.
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);

    // Render Present
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

    // in a old fashion way, we need to delete the registry manually
    // because we allocated it in the heap
    /*if (registry != nullptr)
    {
        delete registry;
        registry = nullptr;
    }*/



    MyLogger::Log("Game resources destroyed");
}
