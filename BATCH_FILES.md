# TwoDEngine Batch Files

This document provides information about the batch files created to simplify building and running the TwoDEngine and its sample game.

## Available Batch Files

### 1. build_run_engine.bat

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

### 2. build_run_sample_game.bat

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

### 3. pack_sample_game.bat

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

### 4. build_run_python_game.bat

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

### 5. pack_python_game.bat

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

## Requirements

- MinGW with g++ compiler
- SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer libraries
- Lua 5.4.6
- Python 3.10.11 (embedded distribution)
- pybind11 2.11.1
- ImGui library

## Notes

- The batch files assume that all dependencies are in their correct locations as specified in the project structure.
- The packaged applications in the 'dist' and 'dist-python' directories can be distributed as standalone applications.
- If you encounter any issues, check that all paths in the batch files match your project structure.
- For Python integration, make sure the embedded Python distribution and pybind11 are correctly set up.
