# Quick Start Guide - macOS

## 🚀 First Time Setup (5 minutes)

```bash
# 1. Run the setup script
./setup_macos.sh

# 2. Build the project
make -f Makefile.macos

# 3. Run the engine
./SDLGameEngine
```

## 🎯 Using VSCode

Press **Cmd+Shift+B** to build and run!

## 📋 Common Commands

```bash
# Build
make -f Makefile.macos

# Run
./SDLGameEngine

# Clean
make -f Makefile.macos clean

# Rebuild all
make -f Makefile.macos rebuild

# Create release package
./pack_engine_macos.sh
```

## 🛠️ VSCode Tasks

| Task | Description |
|------|-------------|
| **Build and Run (Debug)** | Default - Cmd+Shift+B |
| **Build Only** | Compile without running |
| **Clean Build** | Remove build artifacts |
| **Pack Engine (Release)** | Create distribution |

## 📦 Project Structure

```
sdlgameengine/
├── src/              # Your source code
├── external/         # ImGui, Sol2
├── build_macos/      # Build artifacts
├── Makefile.macos    # Build system
└── SDLGameEngine     # Executable
```

## ✅ Installed Libraries

- SDL2, SDL_image, SDL_ttf, SDL_mixer
- GLM (OpenGL Math)
- ImGui (UI)
- Sol2 (Lua bindings)
- pybind11 (Python bindings)

## 🆘 Need Help?

See detailed documentation:
- `BUILD_INSTRUCTIONS_MACOS.md` - Full build guide
- `VSCODE_TASKS_MACOS.md` - VSCode tasks reference
