#!/bin/bash
#
# build_macos_app.sh - Build SDL Game Engine as a macOS .app bundle
#
# This script:
# 1. Builds the project using Makefile.macos
# 2. Creates a proper .app bundle structure
# 3. Copies the executable and resources
# 4. Bundles required dynamic libraries
# 5. Creates Info.plist with proper metadata
#
# Usage: ./build_macos_app.sh [app_name] [version]
#

set -e  # Exit on error

# Configuration
APP_NAME="${1:-SDLGameEngine}"
APP_VERSION="${2:-1.0.0}"
APP_BUNDLE="${APP_NAME}.app"
BUILD_DIR="build_macos"

echo "=== Building macOS App Bundle ==="
echo "App Name: $APP_NAME"
echo "Version: $APP_VERSION"
echo ""

# Step 1: Build the project
echo "Step 1: Building the project..."
make -f Makefile.macos clean
make -f Makefile.macos
echo "✓ Build complete"
echo ""

# Step 2: Create .app bundle structure
echo "Step 2: Creating .app bundle structure..."
rm -rf "$APP_BUNDLE"
mkdir -p "$APP_BUNDLE/Contents/MacOS"
mkdir -p "$APP_BUNDLE/Contents/Resources"
mkdir -p "$APP_BUNDLE/Contents/Frameworks"
echo "✓ Bundle structure created"
echo ""

# Step 3: Copy executable
echo "Step 3: Copying executable..."
cp "./SDLGameEngine" "$APP_BUNDLE/Contents/MacOS/$APP_NAME"
chmod +x "$APP_BUNDLE/Contents/MacOS/$APP_NAME"
echo "✓ Executable copied"
echo ""

# Step 4: Copy resources
echo "Step 4: Copying resources..."
if [ -d "assets" ]; then
    cp -R assets "$APP_BUNDLE/Contents/Resources/"
    echo "✓ Assets copied"
else
    echo "⚠ No assets directory found"
fi

if [ -f "config.json" ]; then
    cp config.json "$APP_BUNDLE/Contents/Resources/"
    echo "✓ Config file copied"
fi
echo ""

# Step 5: Bundle dynamic libraries
echo "Step 5: Bundling dynamic libraries..."
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
            install_name_tool -id "@executable_path/../Frameworks/$lib_name" "$FRAMEWORKS_DIR/$lib_name"

            # Fix dependencies of this library
            fix_library_dependencies "$FRAMEWORKS_DIR/$lib_name"
        fi
    fi
}

# Function to fix library dependencies (recursive)
fix_library_dependencies() {
    local binary="$1"

    # Get all dynamic library dependencies (including @rpath)
    otool -L "$binary" | grep -E '^\s+(@rpath|/(opt/homebrew|usr/local|Library/Frameworks))' | awk '{print $1}' | while read -r dep; do
        local dep_name=$(basename "$dep")

        # Handle @rpath references
        if [[ "$dep" == @rpath/* ]]; then
            # Try to find the library in common Homebrew locations
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

                # Copy if not already copied
                if [ ! -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                    copy_library "$dep"
                fi
            fi

            # Update the reference in the binary
            if [ -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                install_name_tool -change "@rpath/$lib_name" "@executable_path/../Frameworks/$dep_name" "$binary" 2>/dev/null || true
            fi
        else
            # Regular absolute path
            # Copy dependency if not already copied
            if [ -f "$dep" ] && [ ! -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                copy_library "$dep"
            fi

            # Update the reference in the binary
            if [ -f "$FRAMEWORKS_DIR/$dep_name" ]; then
                install_name_tool -change "$dep" "@executable_path/../Frameworks/$dep_name" "$binary" 2>/dev/null || true
            fi
        fi
    done
}

# Get dependencies from the executable
echo "  Analyzing dependencies..."
LIBS=$(otool -L "$EXECUTABLE" | grep -E '^\s+/(opt/homebrew|usr/local|Library/Frameworks)' | awk '{print $1}')

for lib in $LIBS; do
    copy_library "$lib"
done

# Fix executable library paths
echo "  Fixing executable library paths..."
otool -L "$EXECUTABLE" | grep -E '^\s+/(opt/homebrew|usr/local|Library/Frameworks)' | awk '{print $1}' | while read -r lib; do
    lib_name=$(basename "$lib")
    if [ -f "$FRAMEWORKS_DIR/$lib_name" ]; then
        install_name_tool -change "$lib" "@executable_path/../Frameworks/$lib_name" "$EXECUTABLE"
    fi
done

echo "✓ Libraries bundled and paths fixed"
echo ""

# Step 6: Create Info.plist
echo "Step 6: Creating Info.plist..."
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
    <string>com.leolab.${APP_NAME}</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>$APP_NAME</string>
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
</dict>
</plist>
EOF
echo "✓ Info.plist created"
echo ""

# Step 7: Code signing (optional, for distribution)
echo "Step 7: Code signing..."
if command -v codesign &> /dev/null; then
    echo "  Signing app bundle..."
    codesign --force --deep --sign - "$APP_BUNDLE"
    echo "✓ App bundle signed (ad-hoc signature)"
else
    echo "⚠ codesign not found, skipping signing"
fi
echo ""

# Step 8: Verification
echo "Step 8: Verifying app bundle..."
if [ -d "$APP_BUNDLE" ]; then
    APP_SIZE=$(du -sh "$APP_BUNDLE" | cut -f1)
    echo "✓ App bundle created successfully"
    echo "  Location: $PWD/$APP_BUNDLE"
    echo "  Size: $APP_SIZE"
    echo ""

    # Show bundled libraries
    echo "  Bundled libraries:"
    ls -1 "$FRAMEWORKS_DIR" | sed 's/^/    - /'
    echo ""

    # Verify executable
    echo "  Verifying executable dependencies..."
    if otool -L "$EXECUTABLE" | grep -q '/opt/homebrew\|/usr/local'; then
        echo "  ⚠ Warning: Some Homebrew dependencies still referenced"
        echo "    (This is normal for Python and some system libraries)"
    else
        echo "  ✓ All dependencies are bundled or system libraries"
    fi
fi
echo ""

# Step 9: Create DMG (optional)
read -p "Create a DMG for distribution? (y/N): " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    DMG_NAME="${APP_NAME}-${APP_VERSION}.dmg"
    echo "Creating DMG: $DMG_NAME"

    # Remove old DMG if exists
    rm -f "$DMG_NAME"

    # Create DMG
    hdiutil create -volname "$APP_NAME" -srcfolder "$APP_BUNDLE" -ov -format UDZO "$DMG_NAME"

    if [ -f "$DMG_NAME" ]; then
        DMG_SIZE=$(du -sh "$DMG_NAME" | cut -f1)
        echo "✓ DMG created: $DMG_NAME ($DMG_SIZE)"
    fi
fi

echo ""
echo "=== Build Complete ==="
echo ""
echo "To run the app:"
echo "  open $APP_BUNDLE"
echo ""
echo "To test from command line:"
echo "  ./$APP_BUNDLE/Contents/MacOS/$APP_NAME"
echo ""
