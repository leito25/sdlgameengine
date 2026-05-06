# macOS App Bundle Build Guide

This document explains how to build your SDL Game Engine as a standalone macOS `.app` bundle.

## Quick Start

```bash
# Build the app with default settings
./build_macos_app.sh

# Build with custom name and version
./build_macos_app.sh "MyGameEngine" "2.0.0"
```

## What the Script Does

The `build_macos_app.sh` script performs the following steps:

1. **Builds the project** using `Makefile.macos`
2. **Creates .app bundle structure** with proper macOS directories:
   - `Contents/MacOS/` - Contains the executable
   - `Contents/Resources/` - Contains assets and config files
   - `Contents/Frameworks/` - Contains bundled dynamic libraries
3. **Copies the executable** and makes it runnable
4. **Bundles all dynamic libraries** (SDL2, Python, Lua, etc.)
5. **Fixes library paths** to use `@executable_path` for portability
6. **Creates Info.plist** with app metadata
7. **Code signs** the bundle (ad-hoc signature)
8. **Optionally creates a DMG** for distribution

## Output

After running the script, you'll get:

- **SDLGameEngine.app** - A complete macOS application bundle (~39MB)
- Optionally: **SDLGameEngine-1.0.0.dmg** - A disk image for distribution

## Running the App

You have several options to run the built app:

### Option 1: Double-click in Finder
Simply double-click `SDLGameEngine.app` in Finder

### Option 2: Use the `open` command
```bash
open SDLGameEngine.app
```

### Option 3: Run the executable directly
```bash
./SDLGameEngine.app/Contents/MacOS/SDLGameEngine
```

## App Bundle Structure

```
SDLGameEngine.app/
├── Contents/
│   ├── Info.plist              # App metadata
│   ├── MacOS/
│   │   └── SDLGameEngine       # Main executable
│   ├── Resources/
│   │   ├── assets/             # Game assets (images, sounds, etc.)
│   │   └── config.json         # Configuration file
│   └── Frameworks/             # Bundled libraries
│       ├── libSDL2-2.0.0.dylib
│       ├── libSDL2_image-2.0.0.dylib
│       ├── libSDL2_ttf-2.0.0.dylib
│       ├── libSDL2_mixer-2.0.0.dylib
│       ├── liblua.dylib
│       ├── Python              # Python framework
│       └── ... (45+ bundled libraries)
```

## Bundled Libraries

The script automatically bundles all required dynamic libraries:

### Core Libraries
- **SDL2** - Main SDL library
- **SDL2_image** - Image loading (PNG, JPG)
- **SDL2_ttf** - Font rendering
- **SDL2_mixer** - Audio mixing
- **Lua** - Lua scripting engine
- **Python** - Python interpreter

### Image Processing
- libjpeg, libpng, libwebp, libavif
- libaom, libdav1d (video codecs)
- libtiff, libjxl (image formats)

### Audio Processing
- libFLAC, libvorbis, libopus
- libmpg123, libmp3lame
- libfluidsynth (MIDI)
- libgme (game music)

### System Libraries
- freetype, harfbuzz (font rendering)
- glib, gthread (system utilities)

## Distribution

### Creating a DMG

When you run the build script, it will ask if you want to create a DMG:

```
Create a DMG for distribution? (y/N):
```

Press `y` to create a compressed disk image that users can download and mount.

### Sharing Your App

**For Local/Development Use:**
- Just share the `.app` bundle
- Users can drag it to Applications folder

**For Public Distribution:**
1. Create a DMG with the script
2. Share the `.dmg` file
3. Users mount the DMG and drag the app to Applications

**Important:** For public distribution on macOS, you'll need:
- Apple Developer ID certificate for proper code signing
- Notarization for Gatekeeper approval

The current script uses ad-hoc signing (`codesign -s -`), which works for personal use but not for distribution.

## Customization

### Change App Name
```bash
./build_macos_app.sh "MyCustomName"
```

### Change Version Number
```bash
./build_macos_app.sh "MyApp" "2.5.0"
```

### Add an Icon

1. Create an icon file named `icon.icns`
2. Place it in the project root
3. Modify the script to copy it:
```bash
if [ -f "icon.icns" ]; then
    cp icon.icns "$APP_BUNDLE/Contents/Resources/AppIcon.icns"
fi
```
4. Add to `Info.plist`:
```xml
<key>CFBundleIconFile</key>
<string>AppIcon</string>
```

## Troubleshooting

### "App is damaged" Error
This happens due to Gatekeeper. Fix with:
```bash
xattr -cr SDLGameEngine.app
```

### Library Not Found Errors
Check bundled libraries:
```bash
otool -L SDLGameEngine.app/Contents/MacOS/SDLGameEngine
```

All paths should show `@executable_path/../Frameworks/` or system paths.

### App Won't Launch
Run from terminal to see error messages:
```bash
./SDLGameEngine.app/Contents/MacOS/SDLGameEngine
```

### Missing Resources
Ensure your assets are in the `assets/` directory before building.

## Advanced: Manual Code Signing

If you have an Apple Developer ID:

```bash
# Sign with your certificate
codesign --force --deep --sign "Developer ID Application: Your Name" SDLGameEngine.app

# Verify signature
codesign --verify --deep --strict SDLGameEngine.app

# Check signature details
codesign -dv SDLGameEngine.app
```

## System Requirements

**Minimum macOS Version:** 10.15 (Catalina)

The app bundle is portable and includes all dependencies except:
- System frameworks (CoreFoundation, AppKit, etc.)
- Python framework (bundled but may need Python 3.14+ on target system)

## Build Requirements

To build the app, you need:
- Xcode Command Line Tools
- Homebrew packages (installed via `setup_macos.sh`):
  - SDL2, SDL2_image, SDL2_ttf, SDL2_mixer
  - lua@5.4, glm, pybind11
  - Python 3.14+

## File Sizes

- **Uncompressed .app bundle:** ~39 MB
- **Compressed DMG:** ~15-20 MB (estimated)

Most of the size comes from:
- Bundled dynamic libraries (~25 MB)
- Python framework (~10 MB)
- Your executable (~2.3 MB)

## Clean Build

To rebuild from scratch:

```bash
# Clean previous builds
make -f Makefile.macos clean
rm -rf SDLGameEngine.app
rm -f SDLGameEngine-*.dmg

# Build fresh
./build_macos_app.sh
```

## Summary

The `build_macos_app.sh` script creates a fully self-contained macOS application that:

✓ Includes all required libraries  
✓ Works on other Macs without Homebrew  
✓ Can be distributed as a DMG  
✓ Follows macOS app bundle conventions  
✓ Is code-signed (ad-hoc) for local use  

For questions or issues, refer to `BUILD_INSTRUCTIONS_MACOS.md` or check the project README.
