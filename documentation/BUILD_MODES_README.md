# macOS Build Modes - Debug vs Release

This document explains the two build modes available for your SDL Game Engine macOS app.

## Quick Reference

```bash
# DEBUG build - for development
./scripts/build_macos_app_debug.sh

# RELEASE build - for distribution
./scripts/build_macos_app_release.sh
```

## Build Comparison

| Feature | Debug | Release |
|---------|-------|---------|
| **Optimization** | None (O0) | Full (O3 + LTO) |
| **Debug Symbols** | Included (.dSYM) | Stripped |
| **AddressSanitizer** | Enabled | Disabled |
| **Assertions** | Enabled | Disabled |
| **Binary Size** | Larger (~2.5MB) | Smaller (~1.5MB) |
| **Performance** | Slower | Faster |
| **Use Case** | Development | Distribution |
| **Bundle Name** | SDLGameEngine_Debug.app | SDLGameEngine.app |

## Debug Build

### Purpose
For **development**, **testing**, and **debugging** your game engine.

### Features
- ✅ **No Optimizations** (O0) - Makes debugging easier
- ✅ **Debug Symbols** - Full debugging info with `.dSYM` bundle
- ✅ **AddressSanitizer** - Detects memory issues (leaks, buffer overflows)
- ✅ **Assertions** - All `assert()` statements are active
- ✅ **Verbose Warnings** - Extra compiler warnings enabled

### Build Command
```bash
./scripts/build_macos_app_debug.sh [name] [version]

# Examples:
./scripts/build_macos_app_debug.sh
./scripts/build_macos_app_debug.sh "MyGame_Debug" "1.0.0-dev"
```

### Output
- **App Bundle:** `SDLGameEngine_Debug.app`
- **Executable:** `SDLGameEngine_debug`
- **Debug Symbols:** Included in `Contents/Resources/*.dSYM`
- **Size:** ~41-42MB

### Running the Debug Build

**Normal Run:**
```bash
open SDLGameEngine_Debug.app
```

**With AddressSanitizer Output:**
```bash
ASAN_OPTIONS=detect_leaks=1 ./SDLGameEngine_Debug.app/Contents/MacOS/SDLGameEngine_Debug
```

**Debug with LLDB:**
```bash
lldb ./SDLGameEngine_Debug.app/Contents/MacOS/SDLGameEngine_Debug
(lldb) run
(lldb) bt  # backtrace on crash
```

### When to Use Debug Build
- 🔧 Active development
- 🐛 Debugging crashes or issues
- 🧪 Testing new features
- 🔍 Memory leak detection
- 📊 Performance profiling (with instruments)

### Debug Build Warnings
- ⚠️ Runs slower due to no optimizations
- ⚠️ AddressSanitizer adds overhead
- ⚠️ Larger binary size
- ⚠️ **NOT** for distribution
- ⚠️ Will trigger "app is damaged" on other Macs without developer tools

---

## Release Build

### Purpose
For **production**, **distribution**, and **end users**.

### Features
- ✅ **Full Optimizations** (O3 + LTO) - Maximum performance
- ✅ **Link-Time Optimization** - Cross-file optimizations
- ✅ **Stripped Symbols** - Smaller binary size
- ✅ **Native CPU** - Optimized for Apple Silicon
- ✅ **Fast Math** - Faster floating-point operations
- ✅ **Dead Code Elimination** - Removes unused code

### Build Command
```bash
./scripts/build_macos_app_release.sh [name] [version]

# Examples:
./scripts/build_macos_app_release.sh
./scripts/build_macos_app_release.sh "MyGameEngine" "2.0.0"
```

### Output
- **App Bundle:** `SDLGameEngine.app`
- **Executable:** `SDLGameEngine`
- **Debug Symbols:** Stripped
- **Size:** ~39-40MB
- **Optional DMG:** `SDLGameEngine-1.0.0-macOS.dmg`

### Running the Release Build

**Double-click in Finder or:**
```bash
open SDLGameEngine.app
```

**From terminal:**
```bash
./SDLGameEngine.app/Contents/MacOS/SDLGameEngine
```

### Distribution Options

**Option 1: Share the .app bundle**
```bash
# Zip the app
zip -r SDLGameEngine.zip SDLGameEngine.app

# Or create a tarball
tar -czf SDLGameEngine.tar.gz SDLGameEngine.app
```

**Option 2: Create a DMG**
The release script will prompt you to create a DMG:
```
Create a DMG for distribution? (y/N): y
```

This creates a compressed disk image users can mount and install from.

### When to Use Release Build
- 🚀 Production releases
- 📦 Distribution to users
- 🎮 Performance testing
- 📊 Benchmarking
- 🌐 Public demos

### Release Build Notes
- ✅ Maximum performance
- ✅ Smallest binary size
- ✅ Ready for distribution
- ⚠️ Harder to debug (no symbols)
- ⚠️ Still uses ad-hoc signing (for App Store, need Developer ID)

---

## Compiler Flags Comparison

### Debug Build (Makefile.macos.debug)
```bash
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic \
           -g3                            # Full debug info
           -O0                            # No optimization
           -DDEBUG -D_DEBUG              # Debug macros
           -fsanitize=address            # AddressSanitizer
           -fno-omit-frame-pointer       # Better backtraces
```

### Release Build (Makefile.macos.release)
```bash
CXXFLAGS = -std=c++17 -Wall -Wextra \
           -O3                            # Full optimization
           -DNDEBUG                       # Release macro (disables asserts)
           -flto                          # Link-time optimization
           -march=native -mtune=native   # CPU-specific optimizations
           -ffast-math                    # Fast floating-point
           -funroll-loops                 # Loop unrolling
```

---

## Build Workflow

### Typical Development Workflow

1. **Start with Debug:**
   ```bash
   ./scripts/build_macos_app_debug.sh
   ```

2. **Develop and test** with the debug build

3. **Fix any issues** found by AddressSanitizer

4. **Switch to Release** when ready to ship:
   ```bash
   ./scripts/build_macos_app_release.sh
   ```

5. **Final testing** with release build

6. **Create DMG** for distribution

### Testing Both Builds

You can have both builds installed simultaneously:
- `SDLGameEngine_Debug.app` - for development
- `SDLGameEngine.app` - for release testing

They have different bundle identifiers so they won't conflict.

---

## Troubleshooting

### Debug Build Issues

**AddressSanitizer False Positives:**
```bash
# Disable if needed
ASAN_OPTIONS=detect_leaks=0 ./SDLGameEngine_Debug.app/Contents/MacOS/SDLGameEngine_Debug
```

**Slow Performance:**
- Normal for debug builds
- Use release build for performance testing

**Missing .dSYM:**
```bash
dsymutil SDLGameEngine_debug -o SDLGameEngine_debug.dSYM
```

### Release Build Issues

**"App is damaged" Error:**
```bash
xattr -cr SDLGameEngine.app
```

**Can't Debug Crashes:**
- Rebuild with debug symbols
- Or use Console.app to view crash reports

**Performance Issues:**
- Check if running debug build by mistake
- Verify optimizations with: `otool -tV SDLGameEngine.app/Contents/MacOS/SDLGameEngine`

---

## Size Optimization Tips

### Further Reduce Release Build Size

**1. Strip Python if not needed:**
Remove pybind11 includes and Python framework

**2. Static linking:**
Consider static linking for smaller distribution

**3. Compress DMG:**
Already using UDZO (compressed) format

**4. Remove unused assets:**
```bash
# Remove before building
rm -rf assets/unused/
```

---

## Performance Comparison

Expected performance difference between builds:

| Metric | Debug | Release |
|--------|-------|---------|
| **Startup Time** | ~150ms | ~80ms |
| **Frame Rate** | 45-50 FPS | 60 FPS |
| **Memory Usage** | +30% | Baseline |
| **Binary Size** | +60% | Baseline |

*Numbers are approximate and will vary based on actual game logic*

---

## Code Signing for Distribution

### Ad-Hoc Signature (Current)
Both scripts use ad-hoc signing:
```bash
codesign --sign - SDLGameEngine.app
```

This works for:
- ✅ Personal use
- ✅ Internal testing
- ❌ Distribution to others
- ❌ App Store

### Proper Distribution Signing

For wider distribution, you need an Apple Developer ID:

```bash
# Sign with Developer ID
codesign --force --deep --sign "Developer ID Application: Your Name (TEAMID)" \
         --options runtime \
         SDLGameEngine.app

# Notarize with Apple
xcrun notarytool submit SDLGameEngine.zip \
                --apple-id your@email.com \
                --team-id TEAMID \
                --wait

# Staple the ticket
xcrun stapler staple SDLGameEngine.app
```

---

## Summary

### Use Debug Build When:
- 🔧 Developing new features
- 🐛 Fixing bugs
- 🧪 Testing changes
- 🔍 Investigating crashes
- 📊 Profiling performance

### Use Release Build When:
- 🚀 Shipping to users
- 📦 Creating distributions
- 🎮 Final testing
- 📊 Benchmarking performance
- 🌐 Showing demos

---

## Quick Commands Cheat Sheet

```bash
# Build debug
./scripts/build_macos_app_debug.sh

# Build release
./scripts/build_macos_app_release.sh

# Build with custom name/version
./scripts/build_macos_app_debug.sh "MyGame" "1.5.0-beta"
./scripts/build_macos_app_release.sh "MyGame" "1.5.0"

# Run debug with sanitizer
ASAN_OPTIONS=detect_leaks=1 ./SDLGameEngine_Debug.app/Contents/MacOS/SDLGameEngine_Debug

# Debug with LLDB
lldb ./SDLGameEngine_Debug.app/Contents/MacOS/SDLGameEngine_Debug

# Check app size
du -sh *.app

# Clean all builds
make -f Makefile.macos.debug clean
make -f Makefile.macos.release clean
rm -rf *.app *.dmg

# Verify dependencies
otool -L SDLGameEngine.app/Contents/MacOS/SDLGameEngine
```

---

For more information, see:
- `MACOS_APP_BUILD_README.md` - General app building guide
- `BUILD_SUMMARY.md` - Latest build information
- `BUILD_INSTRUCTIONS_MACOS.md` - Setup instructions
