# TwoDEngine

A 2D game engine built with SDL2, ImGui, GLM, and scripting integration (Lua/Sol2 and Python/pybind11).

## Overview

TwoDEngine is a cross-platform 2D game engine that leverages modern C++ and industry-standard libraries to provide a robust foundation for game development. The engine integrates several powerful libraries:

- **SDL2**: Core windowing, rendering, input, and multimedia functionality
- **SDL2_image**: Image loading and texture creation
- **SDL2_ttf**: Font rendering
- **SDL2_mixer**: Audio playback
- **GLM**: Mathematics library for vectors, matrices, and transformations
- **ImGui**: Immediate mode GUI for debugging and tools
- **Lua/Sol2**: Lua scripting integration
- **Python/pybind11**: Python scripting integration

## Project Structure

```
TwoDEngine/
├── assets/                    # Game assets (images, fonts, sounds, etc.)
│   ├── fonts/                 # Font files
│   ├── images/                # Image files
│   ├── sounds/                # Sound files
│   └── tilemaps/              # Tilemap data
├── bin/                       # Compiled binaries and DLLs
├── libs/                      # Third-party libraries
│   ├── glm/                   # GLM mathematics library
│   ├── imgui/                 # ImGui library
│   ├── lua/                   # Lua headers
│   ├── python/                # Python binding headers
│   ├── pybind11/              # pybind11 headers
│   └── sol/                   # Sol2 library (Lua binding)
├── src/                       # Source code
│   └── Main.cpp               # Main application entry point
├── Makefile                   # Build configuration
├── CMakeLists.txt             # CMake build configuration
├── build_run_engine.bat       # Batch file to build and run the engine
├── build_run_sample_game.bat  # Batch file to build and run the sample game
├── pack_sample_game.bat       # Batch file to package the sample game
├── cmake_setup.bat            # CMake setup script
├── .vscode/                   # VS Code configuration
│   ├── tasks.json             # Build and run tasks
│   ├── launch.json            # Debugging configurations
│   └── settings.json          # Editor settings
├── examples/                  # Example applications
│   ├── SimpleGame.cpp         # Sample game using Lua scripting
│   └── PythonGame.cpp         # Sample game using Python scripting
├── README.md                  # Project documentation
├── BATCH_FILES.md             # Batch files documentation
├── CHANGES.md                 # Recent changes and improvements
├── TASKS.md                   # Common tasks and workflows
└── TECHNICAL.md               # Detailed technical documentation
```

## Dependencies

The engine relies on the following external libraries:

1. **SDL2 (2.30.5)**: Simple DirectMedia Layer
2. **SDL2_image (2.8.2)**: Image loading extension for SDL2
3. **SDL2_ttf (2.22.0)**: TrueType font rendering extension for SDL2
4. **SDL2_mixer (2.8.0)**: Audio mixing extension for SDL2
5. **GLM**: OpenGL Mathematics library
6. **ImGui**: Immediate mode GUI library
7. **Lua (5.4.6)**: Scripting language
8. **Sol2**: C++ binding for Lua
9. **Python (3.10.11)**: Python scripting language
10. **pybind11 (2.11.1)**: C++ binding for Python

## Building the Project

### Prerequisites

- MinGW-w64 with GCC (for Windows)
- GNU Make

### Build Steps

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/TwoDEngine.git
   cd TwoDEngine
   ```

2. Build and run the project using the provided batch files:
   ```
   # To build and run the main engine
   build_run_engine.bat

   # To build and run the sample game (Lua)
   build_run_sample_game.bat

   # To build and run the Python game
   build_run_python_game.bat

   # To package the sample game as a standalone application
   pack_sample_game.bat

   # To package the Python game as a standalone application
   pack_python_game.bat
   ```

   Alternatively, you can build and run manually:
   ```
   # Build the engine
   mingw32-make

   # Run the engine
   bin/main.exe
   ```

## Features

- **Window Management**: Create and manage application windows
- **Rendering**: Hardware-accelerated 2D rendering
- **Input Handling**: Keyboard, mouse, and gamepad input
- **Asset Loading**: Load images, fonts, and audio
- **GUI**: Debug interface with ImGui
- **Scripting**: Lua and Python integration for game logic
- **Mathematics**: Vector and matrix operations with GLM

## Usage Example

```cpp
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>
#include <python/PythonBinding.h>

int main(int argc, char* argv[]) {
    // Initialize SDL and extensions
    SDL_Init(SDL_INIT_EVERYTHING);

    // Initialize scripting engines
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    PythonBinding python;
    if (python.isInitialized()) {
        python.runScriptFile("assets/scripts/main.py");
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow("TwoDEngine",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         800, 600,
                                         SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Game loop
    bool running = true;
    while (running) {
        // Handle events
        // Update game state
        // Render scene
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```

## Additional Documentation

The project includes several documentation files:

- **[README.md](README.md)**: Overview and basic usage
- **[TECHNICAL.md](TECHNICAL.md)**: Detailed technical documentation
- **[QUICKSTART.md](QUICKSTART.md)**: Quick start guide for new users
- **[TASKS.md](TASKS.md)**: Common tasks and workflows
- **[VSCODE_TASKS.md](VSCODE_TASKS.md)**: VS Code tasks and debugging guide
- **[BATCH_FILES.md](BATCH_FILES.md)**: Documentation for utility batch files
- **[CHANGES.md](CHANGES.md)**: Recent changes and improvements
- **[CONTRIBUTING.md](CONTRIBUTING.md)**: Guidelines for contributors
- **[CHANGELOG.md](CHANGELOG.md)**: Version history and changes
- **[ROADMAP.md](ROADMAP.md)**: Future development plans
- **[LICENSE](LICENSE)**: MIT License

## Development Setup

### Windows

1. Install MinGW-w64 with GCC
2. Add MinGW bin directory to your PATH
3. Clone the repository
4. Run `mingw32-make` to build

### Required DLLs

The following DLLs must be in the same directory as the executable:
- SDL2.dll
- SDL2_image.dll
- SDL2_ttf.dll
- SDL2_mixer.dll
- lua54.dll
- Python DLLs (various .pyd files from the Python embedded distribution)

## VS Code Integration

TwoDEngine includes comprehensive VS Code integration to streamline development:

### Tasks

The following tasks are available in VS Code (Ctrl+Shift+P > "Tasks: Run Task"):

- **Build Engine (Debug/Release)**: Compile the engine with or without optimizations
- **Run Engine (Debug/Release)**: Build and run the engine using the batch files
- **Build Sample Game (Debug/Release)**: Compile the sample game
- **Run Sample Game (Debug/Release)**: Build and run the sample game using the batch files
- **Build Python Game (Debug/Release)**: Compile the Python game example
- **Run Python Game (Debug/Release)**: Build and run the Python game example
- **Pack Sample Game (Release)**: Create an optimized standalone distribution package for users
- **Pack Sample Game (Debug)**: Create a debug standalone distribution package with debugging symbols

All tasks have been updated to use the batch files, making it easier to build, run, and package the engine and sample game with a single command.

### Debugging

Debugging configurations are provided for both the engine and sample game:

- **Debug Engine**: Launch the engine with the debugger attached
- **Debug Sample Game**: Launch the sample game with the debugger attached
- **Debug Python Game**: Launch the Python game example with the debugger attached
- **Attach to Engine/Sample Game/Python Game**: Attach the debugger to a running process

For detailed information about VS Code tasks and debugging, see [VSCODE_TASKS.md](VSCODE_TASKS.md).

### Setup and Utility Scripts

Several scripts are provided for easy environment configuration and usage:

- **setup.bat**: Downloads and sets up all dependencies using MinGW
- **cmake_setup.bat**: Sets up the project using CMake build system
- **build_run_engine.bat**: Builds and runs the main engine
- **build_run_sample_game.bat**: Builds and runs the sample game (Lua)
- **build_run_python_game.bat**: Builds and runs the Python game example
- **pack_sample_game.bat**: Packages the sample game as a standalone application
- **pack_python_game.bat**: Packages the Python game as a standalone application

For detailed information about these batch files, see [BATCH_FILES.md](BATCH_FILES.md).

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- SDL2 and extensions by the SDL development team
- ImGui by Omar Cornut
- GLM by G-Truc
- Lua by PUC-Rio
- Sol2 by ThePhD
- Python by the Python Software Foundation
- pybind11 by Wenzel Jakob
