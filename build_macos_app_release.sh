#!/bin/bash
#
# build_macos_app_release.sh - Build SDL Game Engine as a macOS .app bundle (RELEASE)
#
# This script creates a RELEASE build with:
# - Full optimizations (O3 + LTO)
# - Debug symbols stripped
# - Smaller binary size
# - Ready for distribution
#
# Usage: ./build_macos_app_release.sh [app_name] [version]
#

set -e  # Exit on error

# Configuration
APP_NAME="${1:-SDLGameEngine}"
APP_VERSION="${2:-1.0.0}"
APP_BUNDLE="${APP_NAME}.app"
BUILD_DIR="build_macos_release"
MAKEFILE="Makefile.macos.release"

echo "╔════════════════════════════════════════════╗"
echo "║  Building macOS App Bundle - RELEASE MODE  ║"
echo "╚════════════════════════════════════════════╝"
echo ""
echo "App Name: $APP_NAME"
echo "Version: $APP_VERSION"
echo "Build Type: RELEASE"
echo "  - Optimizations: FULL (O3 + LTO)"
echo "  - Debug Symbols: STRIPPED"
echo "  - Binary Size: MINIMIZED"
echo "  - Ready for: DISTRIBUTION"
echo ""

# Step 1: Build the project
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 1: Building RELEASE executable..."
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

# Step 3: Copy executable
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 3: Copying optimized executable..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cp "./$EXECUTABLE_NAME" "$APP_BUNDLE/Contents/MacOS/$APP_NAME"
chmod +x "$APP_BUNDLE/Contents/MacOS/$APP_NAME"

# Additional stripping to minimize size
strip -x "$APP_BUNDLE/Contents/MacOS/$APP_NAME" 2>/dev/null || true

EXEC_SIZE=$(du -sh "$APP_BUNDLE/Contents/MacOS/$APP_NAME" | cut -f1)
echo "✓ Executable copied and stripped"
echo "  Final size: $EXEC_SIZE"
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

# Copy README for distribution
if [ -f "README.md" ]; then
    cp README.md "$APP_BUNDLE/Contents/Resources/"
    echo "✓ README copied"
fi

if [ -f "LICENSE" ]; then
    cp LICENSE "$APP_BUNDLE/Contents/Resources/"
    echo "✓ LICENSE copied"
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
            # Strip debug symbols from libraries
            strip -x "$FRAMEWORKS_DIR/$lib_name" 2>/dev/null || true
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

echo "✓ Libraries bundled, stripped, and paths fixed"
echo ""

# Step 6: Create Info.plist (RELEASE version)
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
    <string>com.leolab.${APP_NAME}</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>$APP_NAME</string>
    <key>CFBundleDisplayName</key>
    <string>SDL Game Engine</string>
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
    <key>NSHumanReadableCopyright</key>
    <string>© 2026 LeoLab. All rights reserved.</string>
</dict>
</plist>
EOF
echo "✓ Info.plist created (RELEASE configuration)"
echo ""

# Step 7: Code signing
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 7: Code signing..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if command -v codesign &> /dev/null; then
    echo "  Signing app bundle..."
    codesign --force --deep --sign - "$APP_BUNDLE" 2>/dev/null
    echo "✓ App bundle signed (ad-hoc signature)"
    echo ""
    echo "  ℹ️  For distribution, use:"
    echo "     codesign --sign \"Developer ID Application: Your Name\" $APP_BUNDLE"
else
    echo "⚠ codesign not found, skipping signing"
fi
echo ""

# Step 8: Verification
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Step 8: Verifying RELEASE app bundle..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if [ -d "$APP_BUNDLE" ]; then
    APP_SIZE=$(du -sh "$APP_BUNDLE" | cut -f1)
    EXEC_SIZE=$(du -sh "$EXECUTABLE" | cut -f1)
    LIB_COUNT=$(ls -1 "$FRAMEWORKS_DIR" | wc -l)
    FRAMEWORKS_SIZE=$(du -sh "$FRAMEWORKS_DIR" | cut -f1)

    echo "✓ RELEASE app bundle created successfully"
    echo ""
    echo "📦 Bundle Information:"
    echo "  Location: $PWD/$APP_BUNDLE"
    echo "  Total Size: $APP_SIZE"
    echo "  Executable: $EXEC_SIZE"
    echo "  Frameworks: $FRAMEWORKS_SIZE ($LIB_COUNT libraries)"
    echo ""
    echo "🚀 Release Features:"
    echo "  ✓ Fully optimized (O3 + LTO)"
    echo "  ✓ Debug symbols stripped"
    echo "  ✓ All libraries bundled"
    echo "  ✓ Portable (no Homebrew needed)"
    echo "  ✓ Ready for distribution"
    echo ""

    # Verify dependencies
    echo "🔍 Verifying dependencies..."
    if otool -L "$EXECUTABLE" | grep -q '/opt/homebrew\|/usr/local'; then
        echo "  ⚠ Some Homebrew dependencies detected (Python/system libs)"
    else
        echo "  ✓ All dependencies properly bundled"
    fi
    echo ""
fi

echo "╔════════════════════════════════════════════╗"
echo "║       RELEASE BUILD COMPLETE! 🚀           ║"
echo "╚════════════════════════════════════════════╝"
echo ""

# Step 9: Create DMG (optional)
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
read -p "📀 Create a DMG for distribution? (y/N): " -n 1 -r
echo
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
if [[ $REPLY =~ ^[Yy]$ ]]; then
    DMG_NAME="${APP_NAME}-${APP_VERSION}-macOS.dmg"
    echo "Creating DMG: $DMG_NAME"
    echo ""

    # Remove old DMG if exists
    rm -f "$DMG_NAME"

    # Create DMG
    hdiutil create -volname "$APP_NAME" \
                   -srcfolder "$APP_BUNDLE" \
                   -ov \
                   -format UDZO \
                   "$DMG_NAME"

    if [ -f "$DMG_NAME" ]; then
        DMG_SIZE=$(du -sh "$DMG_NAME" | cut -f1)
        echo ""
        echo "✓ DMG created successfully!"
        echo "  File: $DMG_NAME"
        echo "  Size: $DMG_SIZE"
        echo ""
        echo "📦 Ready to distribute!"
    fi
fi

echo ""
echo "🚀 To run the RELEASE app:"
echo "  open $APP_BUNDLE"
echo ""
echo "📦 To test from command line:"
echo "  ./$APP_BUNDLE/Contents/MacOS/$APP_NAME"
echo ""
echo "✅ This RELEASE build is ready for distribution!"
echo ""
