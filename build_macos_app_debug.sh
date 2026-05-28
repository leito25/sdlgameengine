#!/bin/bash
#
# build_macos_app_debug.sh - Build SDL Game Engine as a macOS .app bundle (DEBUG)
#
# This script creates a DEBUG build with:
# - Debug symbols enabled (dSYM bundle)
# - No optimizations (-O0)
# - AddressSanitizer enabled
# - All assertions enabled
# - Verbose error messages
#
# Usage: ./build_macos_app_debug.sh [app_name] [version]
#

set -e  # Exit on error

# Configuration
APP_NAME="${1:-SDLGameEngine_Debug}"
APP_VERSION="${2:-1.0.0-debug}"
APP_BUNDLE="${APP_NAME}.app"
BUILD_DIR="build_macos_debug"
MAKEFILE="Makefile.macos.debug"

echo "╔════════════════════════════════════════════╗"
echo "║   Building macOS App Bundle - DEBUG MODE   ║"
echo "╚════════════════════════════════════════════╝"
echo ""
echo "App Name: $APP_NAME"
echo "Version: $APP_VERSION"
echo "Build Type: DEBUG"
echo "  - Optimizations: DISABLED (O0)"
echo "  - Debug Symbols: ENABLED"
echo "  - AddressSanitizer: ENABLED"
echo "  - Assertions: ENABLED"
echo ""

# Step 1: Build the project
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 1: Building DEBUG executable..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
make -f "$MAKEFILE" clean
make -f "$MAKEFILE"
EXECUTABLE_NAME=$(grep "^TARGET = " "$MAKEFILE" | cut -d= -f2 | tr -d ' ')
echo "✓ Build complete: $EXECUTABLE_NAME"
echo ""

# Step 2: Create .app bundle structure
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 2: Creating .app bundle structure..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
rm -rf "$APP_BUNDLE"
mkdir -p "$APP_BUNDLE/Contents/MacOS"
mkdir -p "$APP_BUNDLE/Contents/Resources"
mkdir -p "$APP_BUNDLE/Contents/Frameworks"
echo "✓ Bundle structure created"
echo ""

# Step 3: Copy executable and debug symbols
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 3: Copying executable and debug symbols..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cp "./$EXECUTABLE_NAME" "$APP_BUNDLE/Contents/MacOS/$APP_NAME"
chmod +x "$APP_BUNDLE/Contents/MacOS/$APP_NAME"
echo "✓ Executable copied"

# Copy dSYM bundle if it exists
if [ -d "${EXECUTABLE_NAME}.dSYM" ]; then
    cp -R "${EXECUTABLE_NAME}.dSYM" "$APP_BUNDLE/Contents/Resources/"
    echo "✓ Debug symbols (.dSYM) copied"
else
    echo "⚠ No .dSYM file found (creating...)"
    dsymutil "./$EXECUTABLE_NAME" -o "$APP_BUNDLE/Contents/Resources/${EXECUTABLE_NAME}.dSYM"
fi
echo ""

# Step 4: Copy resources
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 4: Copying resources..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if [ -d "assets" ]; then
    cp -R assets "$APP_BUNDLE/Contents/Resources/"
    echo "✓ Assets copied"
fi

if [ -f "config.json" ]; then
    cp config.json "$APP_BUNDLE/Contents/Resources/"
    echo "✓ Config file copied"
fi
echo ""

# Step 5: Bundle dynamic libraries
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 5: Bundling dynamic libraries..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
EXECUTABLE="$APP_BUNDLE/Contents/MacOS/$APP_NAME"
FRAMEWORKS_DIR="$APP_BUNDLE/Contents/Frameworks"

# Function to copy and fix library paths
copy_library() {
    local lib_path="$1"
    local lib_name=$(basename "$lib_path")

    if [ -f "$lib_path" ]; then
        if [ ! -f "$FRAMEWORKS_DIR/$lib_name" ]; then
            cp "$lib_path" "$FRAMEWORKS_DIR/"
            echo "  ✓ Copied: $lib_name"

            # Fix the library's own id
            install_name_tool -id "@executable_path/../Frameworks/$lib_name" "$FRAMEWORKS_DIR/$lib_name" 2>/dev/null || true

            # Fix dependencies of this library
            fix_library_dependencies "$FRAMEWORKS_DIR/$lib_name"
        fi
    fi
}

# Function to fix library dependencies (recursive)
fix_library_dependencies() {
    local binary="$1"

    # Get all dynamic library dependencies (including @rpath)
    otool -L "$binary" 2>/dev/null | grep -E '^\s+(@rpath|/(opt/homebrew|usr/local|Library/Frameworks))' | awk '{print $1}' | while read -r dep; do
        local dep_name=$(basename "$dep")

        # Handle @rpath references
        if [[ "$dep" == @rpath/* ]]; then
            local lib_name=$(basename "$dep")
            local found_path=""

            for search_dir in /opt/homebrew/lib /opt/homebrew/opt/*/lib /usr/local/lib; do
                if [ -f "$search_dir/$lib_name" ]; then
                    found_path="$search_dir/$lib_name"
                    break
                fi
            done

            if [ -n "$found_path" ]; then
                dep="$found_path"
                dep_name=$(basename "$dep")

                if [ ! -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                    copy_library "$dep"
                fi
            fi

            if [ -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                install_name_tool -change "@rpath/$lib_name" "@executable_path/../Frameworks/$dep_name" "$binary" 2>/dev/null || true
            fi
        else
            # Regular absolute path
            if [ -f "$dep" ] && [ ! -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                copy_library "$dep"
            fi

            if [ -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                install_name_tool -change "$dep" "@executable_path/../Frameworks/$dep_name" "$binary" 2>/dev/null || true
            fi
        fi
    done
}

# Get dependencies from the executable
echo "  Analyzing dependencies..."
LIBS=$(otool -L "$EXECUTABLE" 2>/dev/null | grep -E '^\s+/(opt/homebrew|usr/local|Library/Frameworks)' | awk '{print $1}')

for lib in $LIBS; do
    copy_library "$lib"
done

# Fix executable library paths
echo "  Fixing executable library paths..."
otool -L "$EXECUTABLE" 2>/dev/null | grep -E '^\s+/(opt/homebrew|usr/local|Library/Frameworks)' | awk '{print $1}' | while read -r lib; do
    lib_name=$(basename "$lib")
    if [ -f "$FRAMEWORKS_DIR/$lib_name" ]; then
        install_name_tool -change "$lib" "@executable_path/../Frameworks/$lib_name" "$EXECUTABLE" 2>/dev/null || true
    fi
done

echo "✓ Libraries bundled and paths fixed"
echo ""

# Step 6: Create Info.plist (DEBUG version)
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 6: Creating Info.plist..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cat > "$APP_BUNDLE/Contents/Info.plist" << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>en</string>
    <key>CFBundleExecutable</key>
    <string>$APP_NAME</string>
    <key>CFBundleIdentifier</key>
    <string>com.leolab.${APP_NAME}.debug</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>$APP_NAME</string>
    <key>CFBundleDisplayName</key>
    <string>$APP_NAME (Debug)</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>$APP_VERSION</string>
    <key>CFBundleVersion</key>
    <string>$APP_VERSION</string>
    <key>LSMinimumSystemVersion</key>
    <string>10.15</string>
    <key>NSHighResolutionCapable</key>
    <true/>
    <key>NSPrincipalClass</key>
    <string>NSApplication</string>
    <key>LSApplicationCategoryType</key>
    <string>public.app-category.developer-tools</string>
    <key>CFBundleGetInfoString</key>
    <string>DEBUG BUILD - Not for distribution</string>
</dict>
</plist>
EOF
echo "✓ Info.plist created (DEBUG configuration)"
echo ""

# Step 7: Code signing (debug)
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 7: Code signing..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if command -v codesign &> /dev/null; then
    echo "  Signing app bundle (ad-hoc)..."
    codesign --force --deep --sign - "$APP_BUNDLE" 2>/dev/null
    echo "✓ App bundle signed (ad-hoc signature)"
else
    echo "⚠ codesign not found, skipping signing"
fi
echo ""

# Step 8: Verification
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 8: Verifying DEBUG app bundle..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if [ -d "$APP_BUNDLE" ]; then
    APP_SIZE=$(du -sh "$APP_BUNDLE" | cut -f1)
    EXEC_SIZE=$(du -sh "$EXECUTABLE" | cut -f1)
    LIB_COUNT=$(ls -1 "$FRAMEWORKS_DIR" | wc -l)

    echo "✓ DEBUG app bundle created successfully"
    echo ""
    echo "📦 Bundle Information:"
    echo "  Location: $PWD/$APP_BUNDLE"
    echo "  Total Size: $APP_SIZE"
    echo "  Executable Size: $EXEC_SIZE"
    echo "  Bundled Libraries: $LIB_COUNT"
    echo ""
    echo "🐛 Debug Features:"
    echo "  ✓ Debug symbols included (.dSYM)"
    echo "  ✓ AddressSanitizer enabled"
    echo "  ✓ No optimizations (easier debugging)"
    echo "  ✓ All assertions enabled"
    echo ""

    # Show bundled libraries
    echo "📚 Bundled libraries:"
    ls -1 "$FRAMEWORKS_DIR" | head -10 | sed 's/^/    - /'
    if [ "$LIB_COUNT" -gt 10 ]; then
        echo "    ... and $((LIB_COUNT - 10)) more"
    fi
    echo ""
fi

echo "╔════════════════════════════════════════════╗"
echo "║         DEBUG BUILD COMPLETE! 🐛           ║"
echo "╚════════════════════════════════════════════╝"
echo ""
echo "🚀 To run the DEBUG app:"
echo "  open $APP_BUNDLE"
echo ""
echo "🔍 To debug:"
echo "  lldb $APP_BUNDLE/Contents/MacOS/$APP_NAME"
echo ""
echo "📊 To run with sanitizer:"
echo "  ASAN_OPTIONS=detect_leaks=1 ./$APP_BUNDLE/Contents/MacOS/$APP_NAME"
echo ""
echo "⚠️  Note: This DEBUG build is NOT for distribution!"
echo "   Use build_macos_app_release.sh for production builds."
echo ""
