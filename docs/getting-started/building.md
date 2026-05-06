# Building TwoDEngine

This guide covers different ways to build TwoDEngine and explains the build system in detail.

## Build System Overview

TwoDEngine uses **GNU Make** as its primary build system. The Makefile is configured to automatically discover and compile all source files in the `src/` directory.

## Prerequisites

### Windows
- **MinGW-w64**: GCC compiler for Windows
- **Make**: GNU Make (included with MinGW)
- **Git**: For version control

### Linux
```bash
sudo apt-get install build-essential git
```

### macOS
```bash
xcode-select --install
brew install make
```

## Building from Source

### Method 1: Using Make (Recommended)

The Makefile provides several targets for building and managing the project:

```bash
# Build the project
make

# Clean build artifacts
make clean

# Rebuild from scratch
make clean && make

# Build with verbose output
make VERBOSE=1
```

### Method 2: Using Batch Files (Windows Only)

TwoDEngine provides convenient batch files for common workflows:

#### build_and_run.bat
Builds the project and runs the executable:
```cmd
build_and_run.bat
```

#### build_run_engine.bat
Builds, runs, and packages the engine:
```cmd
build_run_engine.bat
```

#### pack_engine.bat
Creates a distributable package:
```cmd
pack_engine.bat
```

## Build Configuration

### Compiler Flags

The Makefile uses the following compiler flags:

```makefile
# C++ Standard
-std=c++17

# Optimization
-O2                    # Optimize for speed

# Warnings
-Wall                  # Enable all warnings
-Wextra               # Enable extra warnings

# Include paths
-Ilibs                # Library headers
-Ilibs/imgui          # ImGui headers
-Ilibs/glm            # GLM headers
-Ilibs/sol            # Sol2 headers
-Ilibs/lua            # Lua headers
-Ipybind11-2.11.1/include  # pybind11 headers
```

### Linker Flags

```makefile
# SDL2 Libraries
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Lua Library
-llua54

# Python Library
-lpython310

# System Libraries
-lopengl32            # OpenGL
-lgdi32               # Windows GDI
```

## Understanding the Makefile

### Source File Discovery

The Makefile automatically finds all `.cpp` files in the `src/` directory:

```makefile
# Automatically find all .cpp files in src directory
SRC_FILES = $(wildcard src/*.cpp)

# Combine with library sources
SRC = $(SRC_FILES) \
      libs/imgui/imgui.cpp \
      libs/imgui/imgui_demo.cpp \
      libs/imgui/imgui_draw.cpp \
      libs/imgui/imgui_widgets.cpp \
      libs/imgui/imgui_sdl.cpp
```

This means you can add new `.cpp` files to the `src/` directory without modifying the Makefile!

### Output Directory

All build artifacts are placed in the `bin/` directory:

```makefile
TARGET = bin/main.exe
```

### Dependencies

The Makefile tracks header dependencies automatically:

```makefile
# Generate dependency files
-MMD -MP
```

## Build Targets

### Default Target (all)
```bash
make
# or simply
make
```
Builds the main executable.

### Clean Target
```bash
make clean
```
Removes all build artifacts:
- Object files (`*.o`)
- Dependency files (`*.d`)
- Executable (`bin/main.exe`)

### Rebuild Target
```bash
make rebuild
```
Equivalent to `make clean && make`.

## Advanced Build Options

### Debug Build

To build with debug symbols and no optimization:

```bash
make CFLAGS="-g -O0 -Wall -Wextra"
```

### Release Build

For maximum optimization:

```bash
make CFLAGS="-O3 -DNDEBUG -Wall -Wextra"
```

### Parallel Build

Speed up compilation using multiple cores:

```bash
make -j4  # Use 4 cores
make -j   # Use all available cores
```

## Build Output

A successful build produces:

```
bin/
├── main.exe              # Main executable
├── SDL2.dll              # SDL2 library
├── SDL2_image.dll        # SDL2_image library
├── SDL2_ttf.dll          # SDL2_ttf library
├── SDL2_mixer.dll        # SDL2_mixer library
└── lua54.dll             # Lua library
```

## Troubleshooting Build Issues

### Issue: "command not found: make"

**Solution**: Install Make
```bash
# Windows (using Chocolatey)
choco install make

# Linux
sudo apt-get install make

# macOS
brew install make
```

### Issue: "undefined reference to SDL_*"

**Solution**: Ensure SDL2 libraries are in the correct location
```bash
# Run setup script
setup.bat  # Windows
./setup.sh # Linux/macOS
```

### Issue: "cannot find -lSDL2"

**Solution**: Check library paths in Makefile
```makefile
LDFLAGS = -Llibs/SDL2/lib -Llibs/lua -Lpython-3.10.11
```

### Issue: Compilation is slow

**Solution**: Use parallel compilation
```bash
make -j4
```

### Issue: Changes not reflected in build

**Solution**: Clean and rebuild
```bash
make clean && make
```

## Build Performance Tips

1. **Use parallel builds**: `make -j`
2. **Use ccache**: Cache compilation results
3. **Incremental builds**: Only modified files are recompiled
4. **Precompiled headers**: Consider using PCH for large projects

## Continuous Integration

### GitHub Actions Example

```yaml
name: Build

on: [push, pull_request]

jobs:
  build:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v2
      - name: Setup MinGW
        uses: egor-tensin/setup-mingw@v2
      - name: Run Setup
        run: setup.bat
      - name: Build
        run: make
      - name: Test
        run: bin/main.exe
```

## Next Steps

- [Running the Engine](running.md)
- [Project Structure](../development/project-structure.md)
- [Contributing](../development/contributing.md)

---

!!! info "Build System"
    TwoDEngine uses GNU Make for its simplicity and cross-platform compatibility. Future versions may include CMake support for more advanced build configurations.
