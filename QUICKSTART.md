# TwoDEngine Quick Start Guide

This guide will help you get started with TwoDEngine quickly. Follow these steps to set up, build, and run your first TwoDEngine application.

## Prerequisites

Before you begin, ensure you have the following installed:
- MinGW-w64 with GCC (for Windows)
- GNU Make

## Getting Started

### 1. Clone or Download the Repository

```bash
git clone https://github.com/yourusername/TwoDEngine.git
cd TwoDEngine
```

### 2. Build the Project

```bash
mingw32-make
```

This will compile the source code and create the executable in the `bin` directory.

### 3. Run the Application

```bash
bin/main.exe
```

You should see a window appear with a blue background and an ImGui window titled "Hello, ImGui!".

## Creating Your First Game

### 1. Modify the Main.cpp File

Open `src/Main.cpp` and start by modifying the existing code. Here's a simple example that creates a moving rectangle:

```cpp
// In the main loop, add:
SDL_Rect rect = {400, 300, 50, 50};
int speed = 5;

// Inside the main loop, before rendering ImGui:
// Update rectangle position based on keyboard input
const Uint8* keystate = SDL_GetKeyboardState(NULL);
if (keystate[SDL_SCANCODE_UP]) rect.y -= speed;
if (keystate[SDL_SCANCODE_DOWN]) rect.y += speed;
if (keystate[SDL_SCANCODE_LEFT]) rect.x -= speed;
if (keystate[SDL_SCANCODE_RIGHT]) rect.x += speed;

// Draw the rectangle (before ImGui rendering)
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &rect);
```

### 2. Adding Assets

1. Place your image files in the `assets/images/` directory
2. Load and display an image:

```cpp
// After creating the renderer:
SDL_Surface* surface = IMG_Load("assets/images/your_image.png");
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
SDL_FreeSurface(surface);

// In the render loop, before ImGui rendering:
SDL_Rect destRect = {100, 100, 64, 64};
SDL_RenderCopy(renderer, texture, NULL, &destRect);

// In the cleanup section:
SDL_DestroyTexture(texture);
```

### 3. Adding Sound

```cpp
// After initializing SDL_mixer:
Mix_Chunk* sound = Mix_LoadWAV("assets/sounds/your_sound.wav");
Mix_Music* music = Mix_LoadMUS("assets/sounds/your_music.mp3");

// Play background music:
Mix_PlayMusic(music, -1);  // -1 means loop indefinitely

// Play sound effect (in response to an event):
Mix_PlayChannel(-1, sound, 0);  // -1 means first available channel, 0 means no loops

// In the cleanup section:
Mix_FreeChunk(sound);
Mix_FreeMusic(music);
```

### 4. Adding Text

```cpp
// After initializing SDL_ttf:
TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 24);

// Render text:
SDL_Color textColor = {255, 255, 255, 255};
SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, TwoDEngine!", textColor);
SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h};
SDL_FreeSurface(textSurface);

// In the render loop, before ImGui rendering:
SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

// In the cleanup section:
SDL_DestroyTexture(textTexture);
TTF_CloseFont(font);
```

### 5. Using Lua Scripting

```cpp
// After initializing Lua:
lua.script(R"(
    function update(dt)
        -- Lua code to update game state
        return "Hello from Lua! dt = " .. dt
    end
)");

// In the game loop:
float deltaTime = 1.0f / 60.0f;  // Simple fixed time step
std::string result = lua["update"](deltaTime);

// Display the result in ImGui:
ImGui::Text("%s", result.c_str());
```

### 6. Using GLM for Math

```cpp
// Example of using GLM for vector operations:
glm::vec2 position(100.0f, 100.0f);
glm::vec2 velocity(1.0f, 1.0f);

// In the game loop:
position += velocity;

// Use the position for rendering:
SDL_Rect rect = {static_cast<int>(position.x), static_cast<int>(position.y), 50, 50};
SDL_RenderFillRect(renderer, &rect);
```

## Building Your Game

After making changes to your code, rebuild the project:

```bash
mingw32-make
```

Then run your game:

```bash
bin/main.exe
```

## Distributing Your Game

To distribute your game, you'll need to include:

1. Your game executable (`bin/main.exe`)
2. All required DLLs:
   - SDL2.dll
   - SDL2_image.dll
   - SDL2_ttf.dll
   - SDL2_mixer.dll
   - lua54.dll
3. Any assets your game uses (images, sounds, fonts, etc.)

## Next Steps

- Read the [README.md](README.md) for an overview of the engine
- Check [TECHNICAL.md](TECHNICAL.md) for detailed technical documentation
- Explore the SDL2, ImGui, GLM, and Lua documentation for more advanced features

## Troubleshooting

### Common Issues

1. **"DLL not found" errors**:
   - Ensure all required DLLs are in the same directory as your executable

2. **Black screen or no window**:
   - Check SDL initialization code and error messages
   - Verify that your rendering code is correct

3. **No sound**:
   - Check that SDL_mixer is properly initialized
   - Verify that sound files exist and are in the correct format

4. **Build errors**:
   - Check that all include paths and library paths are correct in the Makefile
   - Ensure you have the correct versions of all libraries