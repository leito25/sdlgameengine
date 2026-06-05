#!/bin/bash
# setup_linux.sh - Modern setup script for SDL Game Engine on Linux

set -e  # Exit on error

echo "========================================="
echo "SDL Game Engine Setup Script for Linux"
echo "========================================="
echo ""

# Ensure script is run with sudo for package installation
if [ "$EUID" -ne 0 ]; then
    echo "ERROR: Please run this script with sudo!"
    echo "Example: sudo ./scripts/setup.sh"
    exit 1
fi

# Update package lists
echo "Updating package lists..."
apt-get update
echo ""

# Install Essential Build Tools (GCC/G++, Make, etc.)
echo "Checking and installing development tools..."
apt-get install -y build-essential git pkg-config
echo "✓ Development tools installed"
echo ""

# Install dependencies
echo "Installing dependencies..."
echo ""

# SDL2 and extensions (Development libraries)
echo "→ Installing SDL2 libraries..."
apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

# GLM
echo "→ Installing GLM (OpenGL Mathematics)..."
apt-get install -y libglm-dev

# Lua 5.4
echo "→ Installing Lua 5.4..."
apt-get install -y liblua5.4-dev lua5.4

# Python and pybind11
echo "→ Installing Python and pybind11..."
apt-get install -y python3 python3-dev pybind11-dev

echo ""
echo "✓ All system dependencies installed!"
echo ""

# Clone/check external libraries (Drop privileges if run via sudo to keep file ownership clean)
echo "Setting up external libraries..."
# If SUDO_USER is defined, run the git clones as the regular user to prevent permission issues
GIT_CMD="git clone --depth 1"
if [ -n "$SUDO_USER" ]; then
    mkdir -p external
    chown "$SUDO_USER:" external
    RUN_AS_USER="sudo -u $SUDO_USER"
fi

# ImGui
if [ ! -d "external/imgui" ]; then
    echo "→ Cloning ImGui..."
    $RUN_AS_USER $GIT_CMD https://github.com/ocornut/imgui.git external/imgui
else
    echo "✓ ImGui already present"
fi

# Sol2
if [ ! -d "external/sol2" ]; then
    echo "→ Cloning Sol2..."
    $RUN_AS_USER $GIT_CMD https://github.com/ThePhD/sol2.git external/sol2
else
    echo "✓ Sol2 already present"
fi

echo ""
echo "✓ External libraries ready!"
echo ""

# Verify compiler (g++ is the standard on Linux, but can use clang++ if preferred)
if command -v g++ &>/dev/null; then
    echo "✓ Compiler: $(g++ --version | head -n 1)"
else
    echo "ERROR: g++ not found!"
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
echo "  • GLM:        $(pkg-config --modversion glm 2>/dev/null || echo 'header-only / installed')"
echo "  • Lua:        $(pkg-config --modversion lua5.4 2>/dev/null || pkg-config --modversion lua-5.4 2>/dev/null || echo '5.4.x')"
echo "  • pybind11:   $(pkg-config --modversion pybind11 2>/dev/null || echo 'installed')"
echo "  • ImGui:      external/imgui (latest)"
echo "  • Sol2:       external/sol2 (latest)"
echo ""
echo "Next Steps:"
echo "  1. Build the project:    make -f Makefile.linux"
echo "  2. Run the engine:       ./SDLGameEngine"
echo "  3. Or use VSCode:        Ctrl+Shift+B (Build and Run Engine)"
echo ""
echo "VSCode Tasks Available:"
echo "  • Build and Run Engine (Debug)   - Default build task"
echo "  • Build and Run Engine (Release) - Optimized build"
echo "  • Build Only (Linux)             - Compile without running"
echo "  • Clean Build (Linux)            - Remove build artifacts"
echo "  • Rebuild All (Linux)            - Clean and rebuild"
echo ""
