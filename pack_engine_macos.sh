#!/bin/bash
# pack_engine_macos.sh - Package the SDL Game Engine for macOS distribution

set -e  # Exit on error

# Determine build mode (debug or release)
BUILD_MODE="${1:-release}"

if [ "$BUILD_MODE" = "debug" ]; then
    DIST_DIR="dist-debug"
    BUILD_FLAGS=""
    echo "=== Packaging SDLGameEngine in DEBUG mode ==="
else
    DIST_DIR="dist"
    BUILD_FLAGS="CXXFLAGS+='-O3 -DNDEBUG'"
    echo "=== Packaging SDLGameEngine in RELEASE mode ==="
fi

# Clean previous distribution
echo "Cleaning previous distribution..."
rm -rf "$DIST_DIR"
mkdir -p "$DIST_DIR"

# Clean and build
echo "Building the engine..."
make -f Makefile.macos clean
eval make -f Makefile.macos $BUILD_FLAGS

# Copy the executable
echo "Copying executable..."
cp SDLGameEngine "$DIST_DIR/"

# Copy dynamic libraries (frameworks are system-wide on macOS)
echo "Checking for local dynamic libraries..."
# Note: Homebrew libraries are usually system-wide, but we can check
# Use otool to see what libraries the executable needs
otool -L SDLGameEngine | grep -E "(SDL|lua|Python)" | awk '{print $1}' > "$DIST_DIR/required_libs.txt"

# Copy assets if they exist
if [ -d "assets" ]; then
    echo "Copying assets..."
    cp -r assets "$DIST_DIR/"
fi

# Copy documentation
echo "Copying documentation..."
[ -f "README.md" ] && cp README.md "$DIST_DIR/"
[ -f "BUILD_INSTRUCTIONS_MACOS.md" ] && cp BUILD_INSTRUCTIONS_MACOS.md "$DIST_DIR/"

# Create a launcher script
echo "Creating launcher script..."
cat > "$DIST_DIR/run.sh" << 'EOF'
#!/bin/bash
cd "$(dirname "$0")"
./SDLGameEngine
EOF
chmod +x "$DIST_DIR/run.sh"

# Create a README for the distribution
cat > "$DIST_DIR/INSTALL.txt" << EOF
SDL Game Engine - macOS Distribution

Installation Instructions:
1. Ensure you have the required system libraries installed:
   - SDL2 and extensions (SDL_image, SDL_ttf, SDL_mixer)
   - Lua 5.4
   - Python 3.14+

   Install via Homebrew:
   brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer lua@5.4 glm pybind11

2. Run the game:
   ./run.sh

   Or directly:
   ./SDLGameEngine

Build Information:
- Build Mode: $BUILD_MODE
- Architecture: $(uname -m)
- System: $(uname -s) $(uname -r)

Required Libraries (see required_libs.txt for paths):
$(cat "$DIST_DIR/required_libs.txt" | sed 's/^/  - /')

For more information, see BUILD_INSTRUCTIONS_MACOS.md
EOF

# Print size information
echo ""
echo "=== Package Complete ==="
echo "Distribution directory: $DIST_DIR"
echo "Package size: $(du -sh "$DIST_DIR" | awk '{print $1}')"
echo "Executable size: $(ls -lh "$DIST_DIR/SDLGameEngine" | awk '{print $5}')"
echo ""
echo "Contents:"
ls -lh "$DIST_DIR"
echo ""
echo "To test the package:"
echo "  cd $DIST_DIR && ./run.sh"
