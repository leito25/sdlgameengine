# TwoDEngine - Complete Documentation

A comprehensive 2D game engine built with SDL2, ImGui, GLM, and scripting integration (Lua/Sol2 and Python/pybind11).

---

## Table of Contents

1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Dependencies](#dependencies)
4. [Quick Start Guide](#quick-start-guide)
5. [Building the Project](#building-the-project)
6. [Batch Files Reference](#batch-files-reference)
7. [Features](#features)
8. [Python Binding System](#python-binding-system)
9. [Usage Examples](#usage-examples)
10. [VS Code Integration](#vs-code-integration)
11. [Contributing Guidelines](#contributing-guidelines)
12. [Push Instructions](#push-instructions)
13. [Changelog](#changelog)
14. [Recent Changes](#recent-changes)
15. [License](#license)
16. [Acknowledgments](#acknowledgments)

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
└── DOCUMENTATION.md           # This unified documentation file
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

## Quick Start Guide

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

#### 2. Build the Project

```bash
mingw32-make
```

This will compile the source code and create the executable in the `bin` directory.

#### 3. Run the Application

```bash
bin/main.exe
```

You should see a window appear with a blue background and an ImGui window titled "Hello, ImGui!".

### Creating Your First Game

#### 1. Modify the Main.cpp File

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

#### 2. Adding Assets

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

#### 3. Adding Sound

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

#### 4. Adding Text

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

#### 5. Using Lua Scripting

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

#### 6. Using GLM for Math

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

### Building Your Game

After making changes to your code, rebuild the project:

```bash
mingw32-make
```

Then run your game:

```bash
bin/main.exe
```

### Distributing Your Game

To distribute your game, you'll need to include:

1. Your game executable (`bin/main.exe`)
2. All required DLLs (listed in Dependencies section)
3. Any assets your game uses (images, sounds, fonts, etc.)

---

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

### Development Setup

#### Windows

1. Install MinGW-w64 with GCC
2. Add MinGW bin directory to your PATH
3. Clone the repository
4. Run `mingw32-make` to build

---

## Batch Files Reference

This section provides information about the batch files created to simplify building and running the TwoDEngine and its sample game.

### Available Batch Files

#### 1. build_run_engine.bat

This batch file builds and runs the main TwoDEngine application.

**Usage:**
```
build_run_engine.bat [release]
```

**Parameters:**
- `release` (optional): When specified, builds the engine in release mode with optimizations. If omitted, builds in debug mode.

**What it does:**
- Builds the engine in debug or release mode
- Runs the main.exe executable
- Displays a window with ImGui integration

#### 2. build_run_sample_game.bat

This batch file builds and runs the sample game application.

**Usage:**
```
build_run_sample_game.bat [release]
```

**Parameters:**
- `release` (optional): When specified, builds the sample game in release mode with optimizations. If omitted, builds in debug mode.

**What it does:**
- Builds the sample game in debug or release mode
- Runs the SimpleGame.exe executable
- Displays a game window with player and enemy characters

#### 3. pack_sample_game.bat

This batch file packages the sample game as a standalone application.

**Usage:**
```
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

**Use Cases:**
- **Release Mode (Default)**: Creates an optimized build for distribution to users
- **Debug Mode**: Creates a build with debugging symbols for development and testing

#### 4. build_run_python_game.bat

This batch file builds and runs the Python game example.

**Usage:**
```
build_run_python_game.bat [release]
```

**Parameters:**
- `release` (optional): When specified, builds the Python game in release mode with optimizations. If omitted, builds in debug mode.

**What it does:**
- Builds the Python game in debug or release mode
- Runs the PythonGame.exe executable
- Displays a game window with Python-scripted game logic

#### 5. pack_python_game.bat

This batch file packages the Python game as a standalone application.

**Usage:**
```
pack_python_game.bat [debug]
```

**Parameters:**
- `debug` (optional): When specified, builds the Python game in debug mode with debugging symbols and packages it to the 'dist-python-debug' directory. If omitted, builds in release mode and packages to the 'dist-python' directory.

**What it does:**
- Builds the Python game in release or debug mode
- Creates a 'dist-python' directory (for release) or 'dist-python-debug' directory (for debug)
- Copies the executable to the distribution directory
- Copies all necessary DLLs to the distribution directory
- Copies Python DLLs (.pyd files) to the distribution directory
- Copies all assets to the distribution directory
- Creates a self-contained distribution package

**Use Cases:**
- **Release Mode (Default)**: Creates an optimized build for distribution to users
- **Debug Mode**: Creates a build with debugging symbols for development and testing

### Requirements

- MinGW with g++ compiler
- SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer libraries
- Lua 5.4.6
- Python 3.10.11 (embedded distribution)
- pybind11 2.11.1
- ImGui library

### Notes

- The batch files assume that all dependencies are in their correct locations as specified in the project structure.
- The packaged applications in the 'dist' and 'dist-python' directories can be distributed as standalone applications.
- If you encounter any issues, check that all paths in the batch files match your project structure.
- For Python integration, make sure the embedded Python distribution and pybind11 are correctly set up.

---

## Features

- **Window Management**: Create and manage application windows
- **Rendering**: Hardware-accelerated 2D rendering
- **Input Handling**: Keyboard, mouse, and gamepad input
- **Asset Loading**: Load images, fonts, and audio
- **GUI**: Debug interface with ImGui
- **Scripting**: Lua and Python integration for game logic
- **Mathematics**: Vector and matrix operations with GLM

---

## Python Binding System

This section describes the Python binding system used in TwoDEngine, which allows game logic to be written in Python while the core engine functionality is implemented in C++.

### Overview

TwoDEngine provides a Python binding system that enables developers to:
- Write game logic in Python
- Access C++ engine functionality from Python
- Pass data between C++ and Python
- Call Python functions from C++

The binding system is implemented in the `PythonBinding` class, which provides a simple interface for loading Python scripts and exchanging data between C++ and Python.

### PythonBinding Class

The `PythonBinding` class is defined in `libs/python/PythonBinding.h` and provides the following functionality:

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

Python scripts used with TwoDEngine should follow a specific structure to work properly with the binding system:

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

The `examples/PythonGame.cpp` file demonstrates how to use the Python binding system in a simple game:

1. Initialize the Python binding system
2. Load a Python script
3. Call Python functions for game logic
4. Exchange data between C++ and Python
5. Update the game state based on Python logic

To run the example, use the `build_run_python_game.bat` script:

```
build_run_python_game.bat
```

### Pybind11 Example

TwoDEngine includes a practical example of using pybind11 for real C++/Python integration. This example demonstrates how to:

- Expose C++ classes and functions to Python
- Pass data between C++ and Python
- Call Python functions from C++
- Modify C++ objects in Python

#### Example Components

The pybind11 example consists of the following files:

- `examples/Pybind11Example.cpp`: C++ implementation that defines data structures, exposes them to Python, and demonstrates data exchange
- `assets/scripts/pybind11_data_processor.py`: Python script that processes data received from C++
- `build_run_pybind11_example.bat`: Script to build and run the example

#### Data Structures

The example defines two main C++ data structures:

```cpp
// A simple data structure
struct DataPoint {
    std::string name;
    int value;
    double coordinates[2];

    // Methods for manipulating the data
    void print() const;
    void updateValue(int newValue);
    void updateCoordinates(double x, double y);
};

// A data processor class
class DataProcessor {
    std::vector<DataPoint> dataPoints;

public:
    void addDataPoint(const DataPoint& point);
    void clearData();
    std::vector<DataPoint>& getData();
    int calculateSum() const;
    double calculateAverage() const;
};
```

#### Exposing C++ to Python

The example uses pybind11 to expose these C++ structures to Python:

```cpp
PYBIND11_EMBEDDED_MODULE(cpp_data, m) {
    // Expose the DataPoint class to Python
    py::class_<DataPoint>(m, "DataPoint")
        .def(py::init<const std::string&, int, double, double>())
        .def("print", &DataPoint::print)
        .def("updateValue", &DataPoint::updateValue)
        .def("updateCoordinates", &DataPoint::updateCoordinates)
        .def_readwrite("name", &DataPoint::name)
        .def_readwrite("value", &DataPoint::value)
        .def_property("x",
            [](const DataPoint& p) { return p.coordinates[0]; },
            [](DataPoint& p, double x) { p.coordinates[0] = x; })
        .def_property("y",
            [](const DataPoint& p) { return p.coordinates[1]; },
            [](DataPoint& p, double y) { p.coordinates[1] = y; });

    // Expose the DataProcessor class to Python
    py::class_<DataProcessor>(m, "DataProcessor")
        .def(py::init<>())
        .def("addDataPoint", &DataProcessor::addDataPoint)
        .def("clearData", &DataProcessor::clearData)
        .def("getData", &DataProcessor::getData, py::return_value_policy::reference)
        .def("calculateSum", &DataProcessor::calculateSum)
        .def("calculateAverage", &DataProcessor::calculateAverage);
}
```

#### Python Script

The Python script (`pybind11_data_processor.py`) processes data received from C++:

```python
import cpp_data

def process_data(processor):
    """Process data received from C++"""
    # Access C++ data from Python
    data = processor.getData()

    # Modify the data in Python
    for point in data:
        point.value *= 2
        point.x += 0.5
        point.y += 0.5

    # Add a new data point from Python
    processor.addDataPoint(cpp_data.DataPoint("Point C", 30, 5.0, 6.0))

    # Calculate statistics
    print(f"Sum calculated in Python: {processor.calculateSum()}")
    print(f"Average calculated in Python: {processor.calculateAverage()}")

    return "Data processing completed in Python"
```

#### Data Exchange Flow

The example demonstrates bidirectional data exchange:

1. C++ creates data objects and passes them to Python
2. Python accesses and modifies the C++ objects
3. Python creates new C++ objects and passes them back
4. C++ accesses the modified data and new objects

#### Running the Example

To run the pybind11 example, use the `build_run_pybind11_example.bat` script:

```
build_run_pybind11_example.bat
```

This will build the example, copy the necessary files, and run it.

### Simple Python Example

TwoDEngine also includes a simpler approach to C++/Python integration that doesn't require pybind11 or Python development headers. This example demonstrates:

- Exchanging data between C++ and Python using files
- Launching Python from C++
- Processing data in Python and returning results to C++

#### Example Components

The simple Python example consists of the following files:

- `examples/SimplePythonExample.cpp`: C++ implementation that creates data, writes it to a file, launches Python, and reads the processed data
- `assets/scripts/simple_python_example.py`: Python script that reads data from a file, processes it, and writes results back to a file
- `build_run_simple_python_example.bat`: Script to build and run the example

#### Data Exchange Approach

Unlike the pybind11 example which directly exposes C++ classes to Python, this example uses a simpler file-based approach:

1. C++ writes data to a text file in a simple format
2. C++ launches the Python interpreter to run a script
3. Python reads the data from the file
4. Python processes the data
5. Python writes the processed data to another file
6. C++ reads the processed data from the file

#### Advantages of This Approach

This approach has several advantages:

- No need for Python development headers or libraries
- Works with any Python installation
- Simple to understand and implement
- No complex build requirements
- Can be extended to support more complex data structures

It's particularly useful when:

- You don't have access to Python development headers
- You want a simpler integration approach
- You need to exchange data between separate C++ and Python processes
- You're working with a runtime-only Python installation

### Troubleshooting

If you encounter issues with the Python binding system:

1. Make sure Python is properly installed and configured
2. Check that the Python script exists and is in the correct location
3. Verify that the Python script defines all the functions being called from C++
4. Ensure that all required DLLs are in the correct location
5. Check the console output for error messages

### Implementation Details

The current implementation of the `PythonBinding` class is a simulation that doesn't actually use Python. Instead, it simulates the behavior of Python for demonstration purposes. In a real implementation, it would use a library like pybind11 to interact with the Python interpreter.

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

### Setup and Utility Scripts

Several scripts are provided for easy environment configuration and usage:

- **setup.bat**: Downloads and sets up all dependencies using MinGW
- **cmake_setup.bat**: Sets up the project using CMake build system
- **build_run_engine.bat**: Builds and runs the main engine
- **build_run_sample_game.bat**: Builds and runs the sample game (Lua)
- **build_run_python_game.bat**: Builds and runs the Python game example
- **pack_sample_game.bat**: Packages the sample game as a standalone application
- **pack_python_game.bat**: Packages the Python game as a standalone application

---

## Contributing Guidelines

Thank you for considering contributing to TwoDEngine! This section provides guidelines and instructions for contributing to the project.

### Code of Conduct

By participating in this project, you agree to abide by our Code of Conduct. Please be respectful and considerate of others.

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
   - Linux/macOS: Follow the instructions in README.md

### Pull Request Process

1. Create a new branch for your feature or bugfix: `git checkout -b feature/your-feature-name`
2. Make your changes
3. Run tests to ensure your changes don't break existing functionality
4. Update documentation if necessary
5. Submit a pull request with a clear description of the changes

### Coding Standards

Please follow these coding standards when contributing:

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
3. Build and run the examples: `cd examples && mingw32-make && SimpleGame.exe`

### License

By contributing to TwoDEngine, you agree that your contributions will be licensed under the project's MIT License.

### Questions?

If you have any questions about contributing, please create an issue or contact the project maintainers.

Thank you for your contributions!

---

## Push Instructions

Follow these steps to push the TwoDEngine project to a remote repository:

### GitHub

1. Create a new repository on GitHub:
   - Go to https://github.com/new
   - Enter a repository name (e.g., "TwoDEngine")
   - Add a description (optional)
   - Choose public or private visibility
   - Do not initialize with README, .gitignore, or license (we already have these)
   - Click "Create repository"

2. Link your local repository to the remote repository:
   ```bash
   git remote add origin https://github.com/yourusername/TwoDEngine.git
   ```

3. Push your changes to the remote repository:
   ```bash
   git push -u origin main
   ```

### GitLab

1. Create a new project on GitLab:
   - Go to https://gitlab.com/projects/new
   - Enter a project name (e.g., "TwoDEngine")
   - Add a description (optional)
   - Choose visibility level
   - Click "Create project"

2. Link your local repository to the remote repository:
   ```bash
   git remote add origin https://gitlab.com/yourusername/TwoDEngine.git
   ```

3. Push your changes to the remote repository:
   ```bash
   git push -u origin main
   ```

### Bitbucket

1. Create a new repository on Bitbucket:
   - Go to https://bitbucket.org/repo/create
   - Enter a repository name (e.g., "TwoDEngine")
   - Add a description (optional)
   - Choose visibility level
   - Click "Create repository"

2. Link your local repository to the remote repository:
   ```bash
   git remote add origin https://yourusername@bitbucket.org/yourusername/TwoDEngine.git
   ```

3. Push your changes to the remote repository:
   ```bash
   git push -u origin main
   ```

### Using SSH Instead of HTTPS

If you prefer to use SSH instead of HTTPS for authentication:

1. Make sure you have an SSH key set up with your Git provider
2. Use the SSH URL instead of the HTTPS URL when adding the remote:
   ```bash
   git remote add origin git@github.com:yourusername/TwoDEngine.git
   ```

### Verifying Remote Repository

To verify that your remote repository is correctly set up:

```bash
git remote -v
```

This should display the fetch and push URLs for your remote repository.

### Pushing Additional Changes

After making additional changes to your project:

1. Stage your changes:
   ```bash
   git add .
   ```

2. Commit your changes:
   ```bash
   git commit -m "Description of changes"
   ```

3. Push your changes:
   ```bash
   git push
   ```

### Creating Branches

To create and work on a new feature branch:

1. Create and switch to a new branch:
   ```bash
   git checkout -b feature/new-feature
   ```

2. Make your changes, commit them, and push the branch:
   ```bash
   git push -u origin feature/new-feature
   ```

3. Create a pull/merge request on your Git provider's website to merge the changes into the main branch.

---

## Changelog

All notable changes to TwoDEngine will be documented in this section.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### [Unreleased]

#### Added
- Initial project setup
- SDL2 integration (core, image, ttf, mixer)
- GLM mathematics library integration
- ImGui integration with SDL2
- Lua/Sol2 scripting integration
- Basic game loop and rendering
- Example game application
- CMake build system support
- Setup scripts for Windows

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
- Example game

#### Documentation
- README.md with project overview
- TECHNICAL.md with detailed technical documentation
- QUICKSTART.md guide for new users
- API documentation
- Example code with comments

### Types of Changes
- **Added** for new features.
- **Changed** for changes in existing functionality.
- **Deprecated** for soon-to-be removed features.
- **Removed** for now removed features.
- **Fixed** for any bug fixes.
- **Security** in case of vulnerabilities.

---

## Recent Changes

### Batch Files

1. **build_run_engine.bat**
   - Created a batch file to build and run the main engine
   - Added support for debug and release modes
   - Usage: `build_run_engine.bat [release]`

2. **build_run_sample_game.bat**
   - Created a batch file to build and run the sample game
   - Added support for debug and release modes
   - Usage: `build_run_sample_game.bat [release]`

3. **pack_sample_game.bat**
   - Created a batch file to package the sample game as a standalone application
   - Added support for both debug and release modes
   - Copies all necessary files to the dist directory (release) or dist-debug directory (debug)
   - Usage: `pack_sample_game.bat [debug]`

4. **build_run_python_game.bat**
  - Created a batch file to build and run the Python game example
  - Added support for debug and release modes
  - Usage: `build_run_python_game.bat [release]`

5. **pack_python_game.bat**
  - Created a batch file to package the Python game as a standalone application
  - Added support for both debug and release modes
  - Copies all necessary files including Python DLLs to the dist-python directory (release) or dist-python-debug directory (debug)
  - Usage: `pack_python_game.bat [debug]`

### VS Code Tasks

1. **Run Engine Tasks**
  - Updated to use the build_run_engine.bat script
  - Added support for debug and release modes

2. **Run Sample Game Tasks**
  - Updated to use the build_run_sample_game.bat script
  - Added support for debug and release modes

3. **Pack Sample Game Tasks**
  - Split into two separate tasks: Pack Sample Game (Debug) and Pack Sample Game (Release)
  - Updated to use the pack_sample_game.bat script with appropriate parameters
  - Debug task creates a distribution with debugging symbols in the dist-debug directory
  - Release task creates an optimized distribution in the dist directory

4. **Run Python Game Tasks**
  - Added tasks to build and run the Python game example
  - Added support for debug and release modes
  - Uses the build_run_python_game.bat script

5. **Pack Python Game Tasks**
  - Added tasks to package the Python game as a standalone application
  - Split into two separate tasks: Pack Python Game (Debug) and Pack Python Game (Release)
  - Uses the pack_python_game.bat script with appropriate parameters
  - Debug task creates a distribution with debugging symbols in the dist-python-debug directory
  - Release task creates an optimized distribution in the dist-python directory

### Documentation

1. **BATCH_FILES.md**
   - Created documentation for the batch files
   - Included usage instructions and parameters
   - Added documentation for Python-related batch files

2. **TASKS.md**
   - Created a task list for common operations
   - Included both batch file and VS Code task options

3. **README.md**
   - Updated to include information about the batch files
   - Updated the VS Code tasks section
   - Added information about Python scripting integration

4. **TECHNICAL.md**
   - Added detailed documentation about Python/pybind11 integration
   - Included code examples for Python initialization and usage
   - Added troubleshooting information for Python integration

5. **VSCODE_TASKS.md**
   - Updated to include Python game tasks
   - Added debugging configurations for the Python game
   - Added troubleshooting information for Python integration

### Testing

All batch files and VS Code tasks have been tested and are working correctly:

- The engine builds and runs in both debug and release modes
- The sample game builds and runs in both debug and release modes
- The packaging process creates a complete standalone distribution

### Benefits

These changes provide several benefits:

1. **Simplified Workflow**: Users can now build and run the engine and sample game with a single command
2. **Consistent Environment**: The batch files ensure that the correct compiler flags and paths are used
3. **Improved Documentation**: The new documentation files provide clear instructions for common tasks
4. **Flexible Options**: Support for both debug and release modes allows for different development needs

---

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

**Note**: This unified documentation combines information from multiple separate markdown files (README.md, BATCH_FILES.md, CHANGELOG.md, CHANGES.md, CONTRIBUTING.md, PUSH_INSTRUCTIONS.md, PYTHON_BINDING.md, and QUICKSTART.md) into a single comprehensive reference document.
