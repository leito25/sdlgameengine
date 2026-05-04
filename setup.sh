#!/bin/bash

echo "TwoDEngine Setup Script"
echo "====================="
echo ""

# Detect OS
OS="$(uname -s)"
case "${OS}" in
    Linux*)     MACHINE=Linux;;
    Darwin*)    MACHINE=Mac;;
    *)          MACHINE="UNKNOWN:${OS}"
esac

echo "Detected OS: ${MACHINE}"
echo ""

# Function to install compiler on macOS
install_compiler_mac() {
    echo ""
    echo "========================================"
    echo "Installing Clang (Xcode Command Line Tools)..."
    echo "========================================"
    echo ""

    # Check if Xcode Command Line Tools are installed
    if xcode-select -p &>/dev/null; then
        echo "Xcode Command Line Tools already installed."
        return 0
    fi

    echo "Installing Xcode Command Line Tools..."
    echo "A dialog will appear - please follow the prompts to install."
    xcode-select --install

    # Wait for installation
    echo "Waiting for installation to complete..."
    echo "Press Enter after the installation is finished..."
    read -r

    # Verify installation
    if command -v clang++ &>/dev/null || command -v g++ &>/dev/null; then
        echo "Compiler installed successfully!"
        return 0
    else
        echo "ERROR: Compiler installation failed."
        return 1
    fi
}

# Function to install compiler on Linux
install_compiler_linux() {
    echo ""
    echo "========================================"
    echo "Installing GCC/G++..."
    echo "========================================"
    echo ""

    # Detect Linux distribution
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        DISTRO=$ID
    else
        DISTRO="unknown"
    fi

    echo "Detected Linux distribution: ${DISTRO}"

    case "${DISTRO}" in
        ubuntu|debian)
            echo "Installing build-essential package..."
            sudo apt-get update
            sudo apt-get install -y build-essential
            ;;
        fedora|rhel|centos)
            echo "Installing gcc-c++ package..."
            sudo dnf install -y gcc-c++ make
            ;;
        arch|manjaro)
            echo "Installing base-devel package..."
            sudo pacman -S --noconfirm base-devel
            ;;
        *)
            echo "ERROR: Unsupported Linux distribution: ${DISTRO}"
            echo "Please install g++ manually for your distribution."
            return 1
            ;;
    esac

    # Verify installation
    if command -v g++ &>/dev/null; then
        echo "G++ installed successfully!"
        return 0
    else
        echo "ERROR: G++ installation failed."
        return 1
    fi
}

# Check if g++ or clang++ is installed
if command -v g++ &>/dev/null; then
    echo "g++ found: $(g++ --version | head -n 1)"
elif command -v clang++ &>/dev/null; then
    echo "clang++ found: $(clang++ --version | head -n 1)"
    # Create g++ symlink to clang++ if it doesn't exist
    if ! command -v g++ &>/dev/null; then
        echo "Note: Using clang++ as the compiler (g++ not found)"
    fi
else
    echo "WARNING: No C++ compiler found (g++ or clang++)."
    echo "Attempting to install compiler..."

    if [ "${MACHINE}" = "Mac" ]; then
        install_compiler_mac
        if [ $? -ne 0 ]; then
            echo "ERROR: Failed to install compiler on macOS."
            exit 1
        fi
    elif [ "${MACHINE}" = "Linux" ]; then
        install_compiler_linux
        if [ $? -ne 0 ]; then
            echo "ERROR: Failed to install compiler on Linux."
            exit 1
        fi
    else
        echo "ERROR: Unsupported operating system: ${MACHINE}"
        exit 1
    fi
fi

# Check for make
if ! command -v make &>/dev/null; then
    echo "ERROR: make not found. Please install make."
    exit 1
fi

echo "Compiler found. Proceeding with setup..."
echo ""

# Create necessary directories
if [ ! -d "bin" ]; then
    mkdir bin
    echo "Created bin directory."
fi

# Download SDL2 if not already present
if [ ! -d "SDL2-2.30.5" ]; then
    echo "Downloading SDL2..."
    if [ "${MACHINE}" = "Mac" ]; then
        curl -L https://github.com/libsdl-org/SDL/releases/download/release-2.30.5/SDL2-2.30.5.dmg -o SDL2.dmg
        echo "Please install SDL2 from the downloaded DMG file."
        echo "After installation, press Enter to continue..."
        read -r
    else
        echo "Please install SDL2 development libraries using your package manager:"
        echo "  Ubuntu/Debian: sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev"
        echo "  Fedora: sudo dnf install SDL2-devel SDL2_image-devel SDL2_ttf-devel SDL2_mixer-devel"
        echo "  Arch: sudo pacman -S sdl2 sdl2_image sdl2_ttf sdl2_mixer"
        echo ""
        echo "Press Enter after installing SDL2 libraries..."
        read -r
    fi
else
    echo "SDL2 directory exists, skipping download."
fi

# Download and build Lua if not already present
if [ ! -d "lua-5.4.6" ]; then
    echo "Downloading Lua..."
    curl -L https://www.lua.org/ftp/lua-5.4.6.tar.gz -o lua-5.4.6.tar.gz
    echo "Extracting Lua..."
    tar -xzf lua-5.4.6.tar.gz
    echo "Building Lua..."
    cd lua-5.4.6
    if [ "${MACHINE}" = "Mac" ]; then
        make macosx
    else
        make linux
    fi
    cd ..
    echo "Lua downloaded, extracted, and built."
else
    echo "Lua already exists, skipping download and build."
fi

# Download and set up Python if not already present
if [ ! -d "python-3.10.11" ]; then
    echo "Python setup required. Please install Python 3.10+ using your system package manager."
    echo "  macOS: brew install python@3.10"
    echo "  Ubuntu/Debian: sudo apt-get install python3.10 python3.10-dev"
    echo "  Fedora: sudo dnf install python3.10 python3.10-devel"
    echo ""
else
    echo "Python directory exists, skipping setup."
fi

# Download and set up pybind11 if not already present
if [ ! -d "pybind11-2.11.1" ]; then
    echo "Downloading pybind11..."
    curl -L https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.tar.gz -o pybind11-2.11.1.tar.gz
    echo "Extracting pybind11..."
    tar -xzf pybind11-2.11.1.tar.gz
    echo "pybind11 downloaded and extracted."
else
    echo "pybind11 already exists, skipping download."
fi

# Build the project
echo "Building the project..."
make
if [ $? -ne 0 ]; then
    echo "ERROR: Build failed."
    exit 1
fi
echo "Project built successfully."

echo ""
echo "Setup completed successfully!"
echo ""
echo "You can now run the main application with:"
echo "  ./bin/main"
echo ""
echo "Or build and run the examples with:"
echo "  cd examples"
echo "  make"
echo "  ./SimpleGame"
echo ""
echo "Thank you for using TwoDEngine!"
