# VSCode Tasks for macOS

Your VSCode tasks have been updated to fully support macOS! Here's what's available:

## Available Tasks

You can run these tasks from VSCode using:
- **Cmd+Shift+B** - Opens the task menu
- **Cmd+Shift+P** → "Tasks: Run Task" → Select a task

---

### 1. **Setup Environment**
- **Shortcut**: Manual trigger
- **Description**: Runs the setup script to install all dependencies
- **macOS Command**: `./setup.sh` (now uses Homebrew-based setup)
- **Use Case**: First-time setup or when dependencies change

---

### 2. **Build and Run Engine (Debug)** ⭐ *Default Build*
- **Shortcut**: **Cmd+Shift+B** (default build task)
- **Description**: Builds and runs the engine in debug mode
- **macOS Command**: `make -f Makefile.macos && ./SDLGameEngine`
- **Use Case**: Daily development work

---

### 3. **Build and Run Engine (Release)**
- **Shortcut**: Manual trigger
- **Description**: Builds with optimizations and runs the engine
- **macOS Command**: `make -f Makefile.macos CXXFLAGS+='-O3 -DNDEBUG' && ./SDLGameEngine`
- **Use Case**: Testing performance with optimizations

---

### 4. **Pack Engine (Debug)**
- **Shortcut**: Manual trigger
- **Description**: Creates a distributable package with debug symbols
- **macOS Command**: `./pack_engine_macos.sh debug`
- **Output**: `dist-debug/` directory
- **Use Case**: Creating debug builds for testing on other machines

---

### 5. **Pack Engine (Release)**
- **Shortcut**: Manual trigger
- **Description**: Creates an optimized distributable package
- **macOS Command**: `./pack_engine_macos.sh`
- **Output**: `dist/` directory
- **Use Case**: Creating release builds for distribution

---

### 6. **Build Only (macOS)** 🆕
- **Shortcut**: Manual trigger
- **Description**: Compiles the project without running it
- **macOS Command**: `make -f Makefile.macos`
- **Use Case**: Just want to check if code compiles

---

### 7. **Clean Build (macOS)** 🆕
- **Shortcut**: Manual trigger
- **Description**: Removes all build artifacts
- **macOS Command**: `make -f Makefile.macos clean`
- **Use Case**: Clean slate before rebuilding

---

### 8. **Rebuild All (macOS)** 🆕
- **Shortcut**: Manual trigger
- **Description**: Cleans and rebuilds the entire project
- **macOS Command**: `make -f Makefile.macos rebuild`
- **Use Case**: When you want a fresh build from scratch

---

## Quick Start

1. **First Time Setup**:
   ```bash
   # Run the setup script
   ./setup_macos.sh
   ```

2. **Daily Development**:
   - Open VSCode
   - Press **Cmd+Shift+B**
   - Project builds and runs automatically

3. **Create Distribution**:
   - Open command palette: **Cmd+Shift+P**
   - Type "Tasks: Run Task"
   - Select "Pack Engine (Release)"

---

## Files Created/Modified

### Modified:
- `.vscode/tasks.json` - Updated with macOS support for all tasks

### Created:
- `Makefile.macos` - Main build system for macOS
- `pack_engine_macos.sh` - Distribution packaging script
- `setup_macos.sh` - Modern Homebrew-based setup script
- `BUILD_INSTRUCTIONS_MACOS.md` - Detailed build documentation
- `CMakeLists.txt.macos` - CMake alternative build system

---

## Platform-Specific Behavior

All tasks now automatically detect your platform:
- **Windows**: Uses `.bat` scripts and MinGW paths
- **macOS**: Uses `.sh` scripts and Homebrew paths
- **Linux**: Uses `.sh` scripts and system package paths

No need to manually switch between configurations!

---

## Keyboard Shortcuts Summary

| Action | Shortcut |
|--------|----------|
| Build (default) | **Cmd+Shift+B** |
| Run task menu | **Cmd+Shift+P** → "Tasks: Run Task" |
| Show running tasks | **Cmd+Shift+P** → "Tasks: Show Running Tasks" |
| Terminate task | **Cmd+Shift+P** → "Tasks: Terminate Task" |

---

## Troubleshooting

### "Task not found"
- Make sure you've saved `.vscode/tasks.json`
- Restart VSCode

### "Script not executable"
- Run: `chmod +x *.sh`

### "Dependencies not found"
- Run: `./setup_macos.sh`
- Or manually: `brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer glm lua@5.4 pybind11`

---

Happy coding! 🎮
