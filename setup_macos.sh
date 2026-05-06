#!/bin/bash
# setup_macos.sh - Modern setup script for SDL Game Engine on macOS

set -e  # Exit on error

echo "========================================="
echo "SDL Game Engine Setup Script for macOS"
echo "========================================="
echo ""

# Check for Homebrew
if ! command -v brew &>/dev/null; then
    echo "ERROR: Homebrew not found!"
    echo ""
    echo "Homebrew is required to install dependencies."
    echo "Install it from: https://brew.sh"
    echo ""
    echo "Or run this command:"
    echo '/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"'
    exit 1
fi

echo "✓ Homebrew found: $(brew --version | head -n 1)"
echo ""

# Check for Xcode Command Line Tools
echo "Checking for Xcode Command Line Tools..."
if ! xcode-select -p &>/dev/null; then
    echo "Installing Xcode Command Line Tools..."
    xcode-select --install
    echo "Please complete the installation and run this script again."
    exit 0
fi
echo "✓ Xcode Command Line Tools installed"
echo ""

# Update Homebrew
echo "Updating Homebrew..."
brew update
echo ""

# Install dependencies
echo "Installing dependencies..."
echo ""

# SDL2 and extensions
echo "→ Installing SDL2 libraries..."
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer

# GLM
echo "→ Installing GLM (OpenGL Mathematics)..."
brew install glm

# Lua 5.4
echo "→ Installing Lua 5.4..."
brew install lua@5.4
brew link lua@5.4 --force

# Python and pybind11
echo "→ Installing Python and pybind11..."
brew install python3 pybind11

echo ""
echo "✓ All dependencies installed!"
echo ""

# Clone/check external libraries
echo "Setting up external libraries..."
mkdir -p external

# ImGui
if [ ! -d "external/imgui" ]; then
    echo "→ Cloning ImGui..."
    git clone --depth 1 https://github.com/ocornut/imgui.git external/imgui
else
    echo "✓ ImGui already present"
fi

# Sol2
if [ ! -d "external/sol2" ]; then
    echo "→ Cloning Sol2..."
    git clone --depth 1 https://github.com/ThePhD/sol2.git external/sol2
else
    echo "✓ Sol2 already present"
fi

echo ""
echo "✓ External libraries ready!"
echo ""

# Verify compiler
if command -v clang++ &>/dev/null; then
    echo "✓ Compiler: $(clang++ --version | head -n 1)"
else
    echo "ERROR: clang++ not found!"
    exit 1
fi

echo ""
echo "========================================="
echo "Setup Complete!"
echo "========================================="
echo ""
echo "Installed Libraries:"
echo "  • SDL2:       $(pkg-config --modversion sdl2)"
echo "  • SDL_image:  $(pkg-config --modversion SDL2_image)"
echo "  • SDL_ttf:    $(pkg-config --modversion SDL2_ttf)"
echo "  • SDL_mixer:  $(pkg-config --modversion SDL2_mixer)"
echo "  • GLM:        $(pkg-config --modversion glm 2>/dev/null || echo 'header-only')"
echo "  • Lua:        $(pkg-config --modversion lua-5.4)"
echo "  • pybind11:   $(pkg-config --modversion pybind11)"
echo "  • ImGui:      external/imgui (latest)"
echo "  • Sol2:       external/sol2 (latest)"
echo ""
echo "Next Steps:"
echo "  1. Build the project:    make -f Makefile.macos"
echo "  2. Run the engine:       ./SDLGameEngine"
echo "  3. Or use VSCode:        Cmd+Shift+B (Build and Run Engine)"
echo ""
echo "VSCode Tasks Available:"
echo "  • Build and Run Engine (Debug)   - Default build task"
echo "  • Build and Run Engine (Release) - Optimized build"
echo "  • Build Only (macOS)             - Compile without running"
echo "  • Clean Build (macOS)            - Remove build artifacts"
echo "  • Rebuild All (macOS)            - Clean and rebuild"
echo "  • Pack Engine (Debug/Release)    - Create distribution package"
echo ""
