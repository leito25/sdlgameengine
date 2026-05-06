# Build Instructions for macOS Silicon

## Installation Summary

All libraries have been installed and tested on your macOS Silicon system:

### ✅ Installed Libraries

1. **SDL2** v2.32.10 - Core graphics library
2. **SDL_image** v2.8.12 - Image loading (PNG, JPG, etc.)
3. **SDL_ttf** v2.24.0 - TrueType font support
4. **SDL_mixer** v2.8.1 - Audio mixing
5. **GLM** v1.0.3 - OpenGL Mathematics (header-only)
6. **ImGui** v1.92.8 WIP - UI library (cloned to `external/imgui`)
7. **Sol2** - Lua bindings (cloned to `external/sol2`, requires Lua 5.4)
8. **pybind11** v3.0.4 - Python bindings (requires Python 3.14)

### Library Locations

- **Homebrew packages**: `/opt/homebrew/`
- **ImGui**: `external/imgui/`
- **Sol2**: `external/sol2/`
- **Lua**: v5.4.8 (linked via `/opt/homebrew/opt/lua@5.4`)
- **Python**: v3.14.0

## Building Your Project

### Option 1: Using Makefile (Recommended)

```bash
# Build the project
make -f Makefile.macos

# Run the executable
./SDLGameEngine

# Clean build files
make -f Makefile.macos clean

# Rebuild from scratch
make -f Makefile.macos rebuild
```

### Option 2: Using CMake

```bash
# Create build directory
mkdir -p build_cmake
cd build_cmake

# Configure with macOS CMakeLists
cmake -f ../CMakeLists.txt.macos ..

# Build
cmake --build .

# Run
./SDLGameEngine
```

## Test Programs

All test programs are in `build_test/` directory:

```bash
cd build_test

# Test each library individually:
make -f Makefile.01 && ./01_sdl_test        # SDL2
make -f Makefile.02 && ./02_sdl_image_test  # SDL_image
make -f Makefile.03 && ./03_sdl_ttf_test    # SDL_ttf
make -f Makefile.04 && ./04_sdl_mixer_test  # SDL_mixer
make -f Makefile.05 && ./05_glm_test        # GLM
make -f Makefile.06 && ./06_imgui_test      # ImGui
make -f Makefile.07 && ./07_sol2_test       # Sol2 + Lua
make -f Makefile.08 && ./08_pybind11_test   # pybind11 + Python
```

## Current Status

- ✅ All libraries installed and working
- ✅ Individual test programs created and passed
- ✅ Main.cpp updated with all library includes
- ⚠️  `Game.h` / `Game.cpp` need to be implemented or verified

## Next Steps

1. **Verify Game class**: Check if `src/Game.h` and `src/Game.cpp` exist
2. **Add source files**: Update `Makefile.macos` SOURCES section with all .cpp files
3. **Build and test**: Run `make -f Makefile.macos`
4. **Debug if needed**: Fix any compilation errors related to missing Game implementation

## Notes

- The original `CMakeLists.txt` is for Windows (MinGW), left untouched
- Created `CMakeLists.txt.macos` for macOS-specific builds
- Created `Makefile.macos` for direct compilation without CMake
- All external dependencies (ImGui, Sol2) are in `external/` directory
- Build artifacts go to `build_macos/` directory to avoid conflicts
