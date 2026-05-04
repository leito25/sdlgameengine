# TwoDEngine Technical Documentation

This document provides detailed technical information about the TwoDEngine project setup, library integration, and build process.

## Library Integration Details

### SDL2 Integration

SDL2 and its extension libraries (SDL2_image, SDL2_ttf, SDL2_mixer) are integrated as follows:

1. **Directory Structure**:
   - SDL2 headers: `SDL2-2.30.5/x86_64-w64-mingw32/include/SDL2/`
   - SDL2 libraries: `SDL2-2.30.5/x86_64-w64-mingw32/lib/`
   - SDL2 binaries: `SDL2-2.30.5/x86_64-w64-mingw32/bin/`

2. **Include Paths**:
   ```
   -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2
   -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2
   -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2
   -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2
   ```

3. **Library Paths**:
   ```
   -LSDL2-2.30.5/x86_64-w64-mingw32/lib
   -LSDL2_image-2.8.2/x86_64-w64-mingw32/lib
   -LSDL2_ttf-2.22.0/x86_64-w64-mingw32/lib
   -LSDL2_mixer-2.8.0/x86_64-w64-mingw32/lib
   ```

4. **Linked Libraries**:
   ```
   -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
   ```

5. **Required DLLs**:
   - SDL2.dll
   - SDL2_image.dll
   - SDL2_ttf.dll
   - SDL2_mixer.dll

### GLM Integration

GLM is a header-only library located in the `libs/glm/` directory. It's included in the build with:

```
-Ilibs/glm
```

### ImGui Integration

ImGui is integrated with SDL2 using the `imgui_sdl` implementation:

1. **Source Files**:
   - `libs/imgui/imgui.cpp`
   - `libs/imgui/imgui_draw.cpp`
   - `libs/imgui/imgui_widgets.cpp`
   - `libs/imgui/imgui_demo.cpp`
   - `libs/imgui/imgui_sdl.cpp`

2. **Include Path**:
   ```
   -Ilibs/imgui
   ```

3. **Integration with SDL2**:
   - ImGuiSDL::Initialize(renderer, width, height)
   - ImGuiSDL::Render(ImGui::GetDrawData())
   - ImGuiSDL::Deinitialize()

### Lua/Sol2 Integration

Lua and Sol2 are integrated as follows:

1. **Lua**:
   - Headers: `libs/lua/` and `lua-5.4.6/src/`
   - Library: `lua-5.4.6/src/liblua.a`
   - DLL: `lua-5.4.6/src/lua54.dll`

2. **Sol2**:
   - Headers: `libs/sol/`

3. **Include Paths**:
   ```
   -Ilibs/lua -Ilua-5.4.6/src
   ```

4. **Library Path**:
   ```
   -Llua-5.4.6/src
   ```

5. **Linked Library**:
   ```
   -llua
   ```

### Python/pybind11 Integration

Python and pybind11 are integrated as follows:

1. **Python**:
   - Embedded Distribution: `python-3.10.11/`
   - DLLs: Various `.pyd` files in the Python embedded distribution

2. **pybind11**:
   - Headers: `pybind11-2.11.1/include/`
   - Custom Binding Class: `libs/python/PythonBinding.h`

3. **Include Paths**:
   ```
   -Ilibs/python -Ipython-3.10.11 -Ipybind11-2.11.1/include
   ```

4. **Usage Example**:
   ```cpp
   // Initialize Python
   PythonBinding python;
   if (python.isInitialized()) {
       // Register variables
       python.setInt("WINDOW_WIDTH", 800);
       python.setInt("WINDOW_HEIGHT", 600);

       // Load and run Python script
       if (python.runScriptFile("assets/scripts/main.py")) {
           // Call Python functions
           python.callFunction("init");

           // Game loop
           while (running) {
               // Call update function with delta time
               python.setFloat("dt", deltaTime);
               python.callFunction("update");

               // Get values from Python
               int score = python.getInt("player_score");
           }
       }
   }
   ```

5. **Python Script Example**:
   ```python
   # Global variables
   player_x = 400
   player_y = 300
   player_score = 0

   # Initialize the game
   def init():
       global player_x, player_y, player_score
       player_x = 400
       player_y = 300
       player_score = 0
       return True

   # Update game state
   def update():
       global player_x, player_y, player_score
       # Game logic here
       player_score += 1
   ```

## Build Process

The build process is managed by the Makefile, which handles compilation and linking of the project:

1. **Compiler**: g++ (MinGW-w64)
2. **C++ Standard**: C++17
3. **Compilation Flags**: `-std=c++17`
4. **Include Paths**: All library include paths
5. **Library Paths**: All library paths
6. **Linked Libraries**: All required libraries

### Build Steps

1. **Compile Source Files**:
   ```
   g++ -std=c++17 [include_paths] -c [source_file] -o [object_file]
   ```

2. **Link Object Files**:
   ```
   g++ [object_files] -o bin/main.exe [library_paths] [libraries]
   ```

3. **Copy DLLs**:
   ```
   copy [dll_source] bin\
   ```

## Initialization Process

The engine initialization process follows these steps:

1. **Initialize Lua**:
   ```cpp
   sol::state lua;
   lua.open_libraries(sol::lib::base);
   ```

2. **Initialize Python**:
   ```cpp
   PythonBinding python;
   if (python.isInitialized()) {
       // Register engine variables
       python.setInt("WINDOW_WIDTH", WINDOW_WIDTH);
       python.setInt("WINDOW_HEIGHT", WINDOW_HEIGHT);

       // Load and run Python script
       python.runScriptFile("assets/scripts/main.py");
       python.callFunction("init");
   }
   ```

3. **Initialize SDL2**:
   ```cpp
   SDL_Init(SDL_INIT_EVERYTHING);
   ```

3. **Initialize SDL2_image**:
   ```cpp
   IMG_Init(IMG_INIT_PNG);
   ```

4. **Initialize SDL2_ttf**:
   ```cpp
   TTF_Init();
   ```

5. **Initialize SDL2_mixer**:
   ```cpp
   Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
   ```

6. **Create Window and Renderer**:
   ```cpp
   SDL_Window* window = SDL_CreateWindow(...);
   SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   ```

7. **Initialize ImGui**:
   ```cpp
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO();
   ImGui::StyleColorsDark();
   ImGuiSDL::Initialize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
   ```

## Main Loop

The main game loop follows this structure:

```cpp
// Main loop
bool running = true;
SDL_Event event;

while (running) {
    // Handle events
    while (SDL_PollEvent(&event)) {
        // Process ImGui events
        // Process game events
    }

    // Start ImGui frame
    ImGui::NewFrame();

    // Create ImGui windows and UI

    // Clear screen
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);

    // Render game objects

    // Render ImGui
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    // Present renderer
    SDL_RenderPresent(renderer);

    // Cap frame rate
    SDL_Delay(1000 / 60);
}
```

## Cleanup Process

The cleanup process follows these steps:

```cpp
// Cleanup ImGui
ImGuiSDL::Deinitialize();
ImGui::DestroyContext();

// Python cleanup is handled automatically by the PythonBinding destructor
// when the python object goes out of scope

// Cleanup SDL2
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
Mix_CloseAudio();
TTF_Quit();
IMG_Quit();
SDL_Quit();
```

## Troubleshooting

### Common Issues

1. **Missing DLLs**:
   - Ensure all required DLLs are in the same directory as the executable.
   - For Python integration, make sure all `.pyd` files from the Python embedded distribution are included.

2. **Linker Errors**:
   - Check that all library paths and linked libraries are correctly specified in the Makefile.
   - For Python integration, verify that the Python include paths are correct.

3. **Compilation Errors**:
   - Verify that all include paths are correct.
   - Check that the C++ standard is set to C++17 or higher.
   - For pybind11, ensure the include path is correctly set to `pybind11-2.11.1/include`.

4. **Runtime Errors**:
   - Check SDL initialization error messages using `SDL_GetError()`.
   - Verify that all resources (images, fonts, etc.) are correctly loaded.
   - For Python scripts, check for syntax errors or missing functions.

5. **Python Integration Issues**:
   - Verify that the Python embedded distribution is correctly set up.
   - Check that Python scripts are in the correct location (assets/scripts/).
   - Ensure that function names in C++ code match those defined in Python scripts.
   - If using the simplified PythonBinding class, make sure you're only using the supported methods.

## Performance Considerations

1. **Rendering**:
   - Use hardware acceleration (`SDL_RENDERER_ACCELERATED`).
   - Batch rendering operations when possible.
   - Use texture atlases for sprites.

2. **Memory Management**:
   - Properly clean up resources (textures, surfaces, etc.).
   - Use smart pointers for resource management.

3. **Frame Rate**:
   - Implement proper frame rate control.
   - Separate update and render loops if necessary.

## Future Enhancements

1. **Entity Component System (ECS)**:
   - Implement an ECS architecture for game objects.

2. **Physics Integration**:
   - Integrate a physics engine like Box2D.

3. **Asset Management**:
   - Create a robust asset loading and caching system.

4. **Scene Management**:
   - Implement a scene graph and scene management system.

5. **Shader Support**:
   - Add support for custom shaders using SDL2's renderer or OpenGL.

6. **Networking**:
   - Integrate networking capabilities for multiplayer games.

7. **Enhanced Python Integration**:
   - Implement full pybind11 integration with proper Python module exposure.
   - Add support for Python packages and dependencies.
   - Create a more robust Python API for game development.
   - Add hot-reloading of Python scripts during development.

8. **Scripting Language Comparison Tools**:
   - Provide benchmarking tools to compare Lua and Python performance.
   - Create unified scripting API that works with both languages.
   - Add documentation on when to use each scripting language.
