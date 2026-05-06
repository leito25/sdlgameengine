# TwoDEngine

A comprehensive 2D game engine built with SDL2, ImGui, GLM, and scripting integration (Lua/Sol2 and Python/pybind11).

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Project Structure](#project-structure)
4. [Dependencies](#dependencies)
5. [Quick Start](#quick-start)
6. [Building the Project](#building-the-project)
7. [Batch Files & Scripts](#batch-files--scripts)
8. [VS Code Integration](#vs-code-integration)
9. [Python Binding System](#python-binding-system)
10. [Technical Documentation](#technical-documentation)
11. [Usage Examples](#usage-examples)
12. [Roadmap](#roadmap)
13. [Contributing](#contributing)
14. [Changelog](#changelog)
15. [Troubleshooting](#troubleshooting)
16. [License](#license)
17. [Acknowledgments](#acknowledgments)

---

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

---

## Features

- **Window Management**: Create and manage application windows
- **Rendering**: Hardware-accelerated 2D rendering
- **Input Handling**: Keyboard, mouse, and gamepad input
- **Asset Loading**: Load images, fonts, and audio
- **GUI**: Debug interface with ImGui
- **Scripting**: Lua and Python integration for game logic
- **Mathematics**: Vector and matrix operations with GLM
- **Cross-platform**: Windows support with plans for Linux/macOS

---

## Project Structure

```
TwoDEngine/
├── assets/                    # Game assets (images, fonts, sounds, etc.)
│   ├── fonts/                 # Font files
│   ├── images/                # Image files
│   ├── scripts/               # Lua and Python scripts
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
├── examples/                  # Example applications
│   ├── SimpleGame.cpp         # Sample game using Lua scripting
│   └── PythonGame.cpp         # Sample game using Python scripting
├── .vscode/                   # VS Code configuration
│   ├── tasks.json             # Build and run tasks
│   ├── launch.json            # Debugging configurations
│   └── settings.json          # Editor settings
├── Makefile                   # Build configuration
├── CMakeLists.txt             # CMake build configuration
├── build_run_engine.bat       # Batch file to build and run the engine
├── pack_engine.bat            # Batch file to package the engine
├── cmake_setup.bat            # CMake setup script
└── README.md                  # This file
```

---

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

### Required DLLs

The following DLLs must be in the same directory as the executable:
- SDL2.dll
- SDL2_image.dll
- SDL2_ttf.dll
- SDL2_mixer.dll
- lua54.dll
- Python DLLs (various .pyd files from the Python embedded distribution)

---

## Quick Start

This guide will help you get started with TwoDEngine quickly.

### Prerequisites

Before you begin, ensure you have the following installed:
- MinGW-w64 with GCC (for Windows)
- GNU Make

### Getting Started

#### 1. Clone or Download the Repository

```bash
git clone https://github.com/yourusername/TwoDEngine.git
cd TwoDEngine
```

#### 2. Run Setup Script (IMPORTANT)

**⚠️ IMPORTANT**: For IntelliSense to work correctly in VS Code, you **MUST** run the setup script first:

```bash
# Windows
setup.bat

# Linux/macOS
./setup.sh
```

This script will:
- Download SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer
- Download and build Lua 5.4.6
- Set up the project structure
- Configure all necessary paths

#### 3. Build the Project

```bash
mingw32-make
```

This will compile the source code and create the executable in the `bin` directory.

#### 4. Run the Application

```bash
bin/main.exe
```

You should see a window appear with a blue background and an ImGui window titled "Hello, ImGui!".


---

## Building the Project

### Build Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/TwoDEngine.git
   cd TwoDEngine
   ```

2. Build and run the project using the provided batch files:
   ```bash
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
   ```bash
   # Build the engine
   mingw32-make

   # Run the engine
   bin/main.exe
   ```

### Development Setup

#### Windows

1. Install MinGW-w64 with GCC
2. Add MinGW bin directory to your PATH
3. Clone the repository
4. Run `mingw32-make` to build

---

## Batch Files & Scripts

This section provides information about the batch files created to simplify building and running the TwoDEngine.

### Available Batch Files

#### 1. build_run_engine.bat

Builds and runs the main TwoDEngine application.

**Usage:**
```bash
build_run_engine.bat [release]
```

**Parameters:**
- `release` (optional): When specified, builds the engine in release mode with optimizations. If omitted, builds in debug mode.

**What it does:**
- Builds the engine in debug or release mode
- Runs the main.exe executable
- Displays a window with ImGui integration

#### 2. build_run_sample_game.bat

Builds and runs the sample game application.

**Usage:**
```bash
build_run_sample_game.bat [release]
```

**Parameters:**
- `release` (optional): When specified, builds the sample game in release mode with optimizations. If omitted, builds in debug mode.

#### 3. pack_sample_game.bat

Packages the sample game as a standalone application.

**Usage:**
```bash
pack_sample_game.bat [debug]
```

**Parameters:**
- `debug` (optional): When specified, builds the sample game in debug mode with debugging symbols and packages it to the 'dist-debug' directory. If omitted, builds in release mode and packages to the 'dist' directory.

**What it does:**
- Builds the sample game in release or debug mode
- Creates a 'dist' directory (for release) or 'dist-debug' directory (for debug)
- Copies the executable to the distribution directory
- Copies all necessary DLLs to the distribution directory
- Copies all assets to the distribution directory
- Creates a self-contained distribution package

#### 4. build_run_python_game.bat

Builds and runs the Python game example.

**Usage:**
```bash
build_run_python_game.bat [release]
```

#### 5. pack_python_game.bat

Packages the Python game as a standalone application.

**Usage:**
```bash
pack_python_game.bat [debug]
```

### Requirements

- MinGW with g++ compiler
- SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer libraries
- Lua 5.4.6
- Python 3.10.11 (embedded distribution)
- pybind11 2.11.1
- ImGui library

---

## VS Code Integration

TwoDEngine includes comprehensive VS Code integration to streamline development.

### IntelliSense Setup

**⚠️ IMPORTANT**: For IntelliSense to work correctly in VS Code, you **MUST** run the setup script first:

```bash
# Windows
setup.bat

# Linux/macOS
./setup.sh
```

**Or** use the VS Code task: `Ctrl+Shift+P` → `Tasks: Run Task` → `Setup Environment`

**Why is this required?**
- The setup script downloads and extracts all required libraries (SDL2, Lua, etc.)
- IntelliSense needs these library paths to resolve headers like `<SDL.h>`, `<lua.h>`, and `<pybind11/pybind11.h>`
- Without running setup first, you'll see red squiggles and "cannot open source file" errors
- The [`.vscode/c_cpp_properties.json`](.vscode/c_cpp_properties.json) configuration references these library paths

**What gets configured:**
- SDL2 libraries: `SDL2-2.30.5/`, `SDL2_image-2.8.2/`, `SDL2_ttf-2.22.0/`, `SDL2_mixer-2.8.0/`
- Lua: `lua-5.4.6/src/`
- Python: System Python at `C:/Python314/include`
- pybind11: `pybind11-2.11.1/include/`
- Other libs: GLM, ImGui, Sol2 in `libs/` directory

After running setup, reload VS Code window (`Ctrl+Shift+P` → `Developer: Reload Window`) to refresh IntelliSense.

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

### Debugging

Debugging configurations are provided for both the engine and sample game:

- **Debug Engine**: Launch the engine with the debugger attached
- **Debug Sample Game**: Launch the sample game with the debugger attached
- **Debug Python Game**: Launch the Python game example with the debugger attached
- **Attach to Engine/Sample Game/Python Game**: Attach the debugger to a running process

---

## Python Binding System

TwoDEngine provides a Python binding system that enables developers to write game logic in Python while the core engine functionality is implemented in C++.

### Overview

The binding system allows you to:
- Write game logic in Python
- Access C++ engine functionality from Python
- Pass data between C++ and Python
- Call Python functions from C++

### PythonBinding Class

The `PythonBinding` class is defined in [`libs/python/PythonBinding.h`](libs/python/PythonBinding.h) and provides the following functionality:

#### Initialization

```cpp
PythonBinding python;
if (!python.isInitialized()) {
    std::cerr << "Failed to initialize Python" << std::endl;
    return 1;
}
```

#### Loading Python Scripts

```cpp
if (!python.runScriptFile("assets/scripts/myscript.py")) {
    std::cerr << "Failed to load Python script" << std::endl;
    return 1;
}
```

#### Calling Python Functions

```cpp
// Call a Python function with no arguments
python.callFunction("init");

// Call a Python function that handles player shooting
python.callFunction("player_shoot");
```

#### Data Exchange

The binding system supports exchanging various data types between C++ and Python:

##### Integers

```cpp
// Set an integer variable in Python
python.setInt("player_health", 100);

// Get an integer variable from Python
int health = python.getInt("player_health", 0); // Default value is 0 if not found
```

##### Floating Point Numbers

```cpp
// Set a float variable in Python
python.setFloat("player_x", 400.0f);

// Get a float variable from Python
float x = python.getFloat("player_x", 0.0f); // Default value is 0.0f if not found
```

##### Strings

```cpp
// Set a string variable in Python
python.setString("player_name", "Player1");

// Get a string variable from Python
std::string name = python.getString("player_name", "Unknown"); // Default value is "Unknown" if not found
```

##### Booleans

```cpp
// Set a boolean variable in Python
python.setBool("is_game_over", false);

// Get a boolean variable from Python
bool gameOver = python.getBool("is_game_over", false); // Default value is false if not found
```

### Python Script Structure

Python scripts used with TwoDEngine should follow a specific structure:

```python
# Game constants
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

# Global variables
player_x = 400
player_y = 300
player_health = 100
player_score = 0
is_game_over = False

# Initialize the game
def init():
    global player_x, player_y, player_health, player_score, is_game_over
    player_x = 400
    player_y = 300
    player_health = 100
    player_score = 0
    is_game_over = False
    print("Game initialized from Python")

# Update game state
def update():
    global player_health, player_score, is_game_over
    # Update game logic here
    pass

# Handle player shooting
def player_shoot():
    global player_score
    player_score += 10
    return True

# Reset the game
def reset_game():
    init()
    print("Game reset from Python")
```

### Example Usage

The [`examples/PythonGame.cpp`](examples/PythonGame.cpp) file demonstrates how to use the Python binding system in a simple game. To run the example:

```bash
build_run_python_game.bat
```

### Pybind11 Integration

TwoDEngine includes a practical example of using pybind11 for real C++/Python integration. This example demonstrates how to expose C++ classes and functions to Python, pass data between C++ and Python, and modify C++ objects in Python.

See the pybind11 example files:
- [`examples/Pybind11Example.cpp`](examples/Pybind11Example.cpp)
- [`assets/scripts/pybind11_data_processor.py`](assets/scripts/pybind11_data_processor.py)

To run the pybind11 example:

```bash
build_run_pybind11_example.bat
```

---

## Technical Documentation

### Library Integration Details

#### SDL2 Integration

SDL2 and its extension libraries are integrated with the following structure:

1. **Include Paths**:
   ```
   -ISDL2-2.30.5/x86_64-w64-mingw32/include/SDL2
   -ISDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2
   -ISDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2
   -ISDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2
   ```

2. **Linked Libraries**:
   ```
   -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
   ```

#### GLM Integration

GLM is a header-only library located in the `libs/glm/` directory.

#### ImGui Integration

ImGui is integrated with SDL2 using the `imgui_sdl` implementation:

- Source files in `libs/imgui/`
- Integration functions: `ImGuiSDL::Initialize()`, `ImGuiSDL::Render()`, `ImGuiSDL::Deinitialize()`

#### Lua/Sol2 Integration

- Lua headers: `libs/lua/` and `lua-5.4.6/src/`
- Sol2 headers: `libs/sol/`
- Library: `lua-5.4.6/src/liblua.a`
- DLL: `lua-5.4.6/src/lua54.dll`

#### Python/pybind11 Integration

- Python embedded distribution: `python-3.10.11/`
- pybind11 headers: `pybind11-2.11.1/include/`
- Custom binding class: `libs/python/PythonBinding.h`

### Build Process

The build process is managed by the Makefile:

1. **Compiler**: g++ (MinGW-w64)
2. **C++ Standard**: C++17
3. **Compilation Flags**: `-std=c++17`

### Initialization Process

The engine initialization follows these steps:

1. Initialize Lua
2. Initialize Python
3. Initialize SDL2 and extensions
4. Create window and renderer
5. Initialize ImGui

### Main Loop Structure

```cpp
while (running) {
    // Handle events
    while (SDL_PollEvent(&event)) {
        // Process events
    }

    // Start ImGui frame
    ImGui::NewFrame();

    // Create ImGui UI

    // Clear screen
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

### Performance Considerations

1. **Rendering**:
   - Use hardware acceleration (`SDL_RENDERER_ACCELERATED`)
   - Batch rendering operations when possible
   - Use texture atlases for sprites

2. **Memory Management**:
   - Properly clean up resources (textures, surfaces, etc.)
   - Use smart pointers for resource management

3. **Frame Rate**:
   - Implement proper frame rate control
   - Separate update and render loops if necessary

---

## Usage Examples

### Basic Engine Usage

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

---

## Roadmap

### Short-term Goals (Next 3 Months)

#### Core Engine Improvements
- [ ] Implement entity component system (ECS) architecture
- [ ] Add resource management system for assets
- [ ] Improve rendering performance
- [ ] Add support for sprite batching
- [ ] Implement scene management system

#### Graphics
- [ ] Add support for sprite animations
- [ ] Implement particle system
- [ ] Add support for post-processing effects
- [ ] Implement basic lighting system
- [ ] Add support for tilemaps

#### Physics
- [ ] Integrate Box2D physics engine
- [ ] Add collision detection and response
- [ ] Implement raycasting
- [ ] Add support for joints and constraints

#### Audio
- [ ] Improve audio management system
- [ ] Add support for 3D audio
- [ ] Implement audio effects (reverb, echo, etc.)
- [ ] Add streaming audio support

#### Scripting
- [ ] Enhance Lua integration
- [ ] Add script hot-reloading
- [ ] Create more comprehensive API for scripts
- [ ] Add visual scripting system

#### Tools
- [ ] Create level editor
- [ ] Implement asset pipeline
- [ ] Add profiling tools
- [ ] Create animation editor

### Medium-term Goals (6-12 Months)

#### Core Engine
- [ ] Implement multi-threading support
- [ ] Add networking capabilities
- [ ] Create plugin system
- [ ] Improve cross-platform support

#### Graphics
- [ ] Add support for skeletal animations
- [ ] Implement advanced shader system
- [ ] Add support for render targets
- [ ] Implement deferred rendering

#### UI
- [ ] Create comprehensive UI system
- [ ] Add support for UI animations
- [ ] Implement UI theming
- [ ] Add support for localization

### Long-term Goals (1+ Years)

#### Core Engine
- [ ] Implement virtual reality support
- [ ] Add augmented reality capabilities
- [ ] Create mobile platform support
- [ ] Implement cloud save/sync features

#### Graphics
- [ ] Add support for 3D rendering
- [ ] Implement physically-based rendering
- [ ] Add support for global illumination
- [ ] Implement advanced post-processing pipeline

#### AI
- [ ] Create behavior tree system
- [ ] Implement pathfinding algorithms
- [ ] Add support for machine learning integration
- [ ] Create procedural generation tools

#### Ecosystem
- [ ] Establish asset marketplace
- [ ] Create community plugin repository
- [ ] Implement template project system
- [ ] Create comprehensive documentation and tutorials

### Versioning Plan

- **v1.x**: Current stable release with incremental improvements
- **v2.0**: Major release with ECS architecture and improved rendering
- **v3.0**: Major release with advanced physics and networking
- **v4.0**: Major release with 3D support and advanced tools

---

## Contributing

Thank you for considering contributing to TwoDEngine! We welcome contributions from the community.

### How to Contribute

There are many ways to contribute to TwoDEngine:

1. **Reporting Bugs**: If you find a bug, please create an issue with a detailed description.
2. **Suggesting Enhancements**: Have an idea for a new feature? Create an issue to discuss it.
3. **Code Contributions**: Want to fix a bug or add a feature? Submit a pull request.
4. **Documentation**: Help improve the documentation by fixing errors or adding examples.
5. **Examples**: Create new example applications that demonstrate how to use TwoDEngine.

### Development Setup

1. Fork the repository
2. Clone your fork: `git clone https://github.com/yourusername/TwoDEngine.git`
3. Set up the development environment:
   - Windows: Run `setup.bat` or `cmake_setup.bat`
   - Linux/macOS: Follow the instructions in this README

### Pull Request Process

1. Create a new branch for your feature or bugfix: `git checkout -b feature/your-feature-name`
2. Make your changes
3. Run tests to ensure your changes don't break existing functionality
4. Update documentation if necessary
5. Submit a pull request with a clear description of the changes

### Coding Standards

#### C++ Style

- Use 4 spaces for indentation (no tabs)
- Follow the existing code style
- Use meaningful variable and function names
- Add comments for complex code sections

#### Commit Messages

- Use clear, descriptive commit messages
- Start with a verb in the present tense (e.g., "Add feature" not "Added feature")
- Reference issue numbers when applicable

#### Documentation

- Document all public functions and classes
- Keep documentation up-to-date with code changes
- Use clear, concise language

### Testing

Before submitting a pull request, please test your changes:

1. Build the project: `mingw32-make` or `cmake --build build`
2. Run the main application: `bin/main.exe`
3. Build and run the examples

### Code of Conduct

By participating in this project, you agree to abide by our Code of Conduct. Please be respectful and considerate of others.

### License

By contributing to TwoDEngine, you agree that your contributions will be licensed under the project's MIT License.

---

## Changelog

All notable changes to TwoDEngine are documented in this section.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### [Unreleased]

#### Added
- Initial project setup
- SDL2 integration (core, image, ttf, mixer)
- GLM mathematics library integration
- ImGui integration with SDL2
- Lua/Sol2 scripting integration
- Python/pybind11 scripting integration
- Basic game loop and rendering
- Example game applications
- CMake build system support
- Setup scripts for Windows
- Batch files for building and packaging
- VS Code integration with tasks and debugging

### [1.0.0] - 2026-04-29

#### Added
- Initial release
- Core engine functionality
- Window management
- Input handling
- Rendering system
- Asset loading
- ImGui integration
- Lua scripting
- Python scripting
- Example games

#### Documentation
- README.md with project overview
- Technical documentation
- Quick start guide
- API documentation
- Example code with comments

### Types of Changes
- **Added** for new features
- **Changed** for changes in existing functionality
- **Deprecated** for soon-to-be removed features
- **Removed** for now removed features
- **Fixed** for any bug fixes
- **Security** in case of vulnerabilities

---

## Troubleshooting

### Common Issues

1. **"DLL not found" errors**:
   - Ensure all required DLLs are in the same directory as your executable
   - For Python integration, make sure all `.pyd` files from the Python embedded distribution are included

2. **Black screen or no window**:
   - Check SDL initialization code and error messages using `SDL_GetError()`
   - Verify that your rendering code is correct

3. **No sound**:
   - Check that SDL_mixer is properly initialized
   - Verify that sound files exist and are in the correct format

4. **Build errors**:
   - Check that all include paths and library paths are correct in the Makefile
   - Ensure you have the correct versions of all libraries
   - For pybind11, ensure the include path is correctly set to `pybind11-2.11.1/include`

5. **IntelliSense errors in VS Code**:
   - Make sure you've run the setup script (`setup.bat` or `./setup.sh`)
   - Reload VS Code window: `Ctrl+Shift+P` → `Developer: Reload Window`
   - Check that [`.vscode/c_cpp_properties.json`](.vscode/c_cpp_properties.json) has the correct paths

6. **Python Integration Issues**:
   - Verify that the Python embedded distribution is correctly set up
   - Check that Python scripts are in the correct location (`assets/scripts/`)
   - Ensure that function names in C++ code match those defined in Python scripts
   - Check the console output for error messages

7. **Linker Errors**:
   - Check that all library paths and linked libraries are correctly specified in the Makefile
   - For Python integration, verify that the Python include paths are correct

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.

---

## Acknowledgments

- SDL2 and extensions by the SDL development team
- ImGui by Omar Cornut
- GLM by G-Truc
- Lua by PUC-Rio
- Sol2 by ThePhD
- Python by the Python Software Foundation
- pybind11 by Wenzel Jakob

---

**Note**: This comprehensive README combines information from multiple documentation files into a single reference document for easy access to all project information.
