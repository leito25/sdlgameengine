# API Reference Overview

Welcome to the TwoDEngine API Reference. This section provides detailed documentation for all classes, methods, and functions in the engine.

## Core Classes

### Game Engine Core

| Class | Description | Status |
|-------|-------------|--------|
| [`Game`](game.md) | Main game engine class managing the game lifecycle | ✅ Implemented |
| `Window` | Window management and rendering context | 🚧 Planned |
| `Renderer` | 2D rendering system | 🚧 Planned |
| `AssetManager` | Asset loading and management | 🚧 Planned |

### Entity Component System

| Class | Description | Status |
|-------|-------------|--------|
| `Entity` | Base entity class | 🚧 Planned |
| `Component` | Base component class | 🚧 Planned |
| `System` | Base system class | 🚧 Planned |
| `Registry` | Entity-component registry | 🚧 Planned |

### Graphics

| Class | Description | Status |
|-------|-------------|--------|
| `Sprite` | 2D sprite rendering | 🚧 Planned |
| `Texture` | Texture management | 🚧 Planned |
| `Animation` | Sprite animation system | 🚧 Planned |
| `Camera` | 2D camera system | 🚧 Planned |

### Input

| Class | Description | Status |
|-------|-------------|--------|
| `InputManager` | Input handling system | 🚧 Planned |
| `Keyboard` | Keyboard input | 🚧 Planned |
| `Mouse` | Mouse input | 🚧 Planned |
| `Gamepad` | Controller input | 🚧 Planned |

### Audio

| Class | Description | Status |
|-------|-------------|--------|
| `AudioManager` | Audio system management | 🚧 Planned |
| `Sound` | Sound effect playback | 🚧 Planned |
| `Music` | Background music playback | 🚧 Planned |

### Scripting

| Class | Description | Status |
|-------|-------------|--------|
| `LuaScript` | Lua script execution | 🚧 Planned |
| `PythonScript` | Python script execution | 🚧 Planned |
| `ScriptManager` | Script management | 🚧 Planned |

## API Documentation Generation

The API documentation is generated from source code comments using **Doxygen**. This ensures the documentation stays in sync with the code.

### Viewing Full API Documentation

To generate and view the complete API documentation:

```bash
# Generate Doxygen documentation
doxygen Doxyfile

# Open the documentation
# Windows
start docs/api/html/index.html

# Linux
xdg-open docs/api/html/index.html

# macOS
open docs/api/html/index.html
```

## Documentation Conventions

### Method Documentation

All public methods are documented with:

- **Brief description**: One-line summary
- **Detailed description**: Comprehensive explanation
- **Parameters**: All parameters with types and descriptions
- **Return value**: Return type and description
- **Exceptions**: Any exceptions that may be thrown
- **Example**: Usage example code
- **See also**: Related methods or classes

### Example

```cpp
/**
 * @brief Initialize the game engine
 *
 * This method initializes all engine subsystems including:
 * - SDL2 video and audio
 * - Window and renderer
 * - Asset manager
 * - Input system
 *
 * @return true if initialization succeeded, false otherwise
 *
 * @throws std::runtime_error if SDL initialization fails
 *
 * @note This method must be called before Run()
 * @warning Calling Initialize() multiple times without Destroy() may cause memory leaks
 *
 * @see Run(), Destroy()
 *
 * @code
 * Game game;
 * if (game.Initialize()) {
 *     game.Run();
 *     game.Destroy();
 * }
 * @endcode
 */
bool Initialize();
```

## Code Examples

Each class documentation includes:

1. **Basic usage example**: Simple, minimal code
2. **Advanced example**: Real-world usage scenario
3. **Best practices**: Recommended patterns
4. **Common pitfalls**: What to avoid

## API Stability

TwoDEngine follows semantic versioning:

- **Major version** (X.0.0): Breaking API changes
- **Minor version** (0.X.0): New features, backward compatible
- **Patch version** (0.0.X): Bug fixes, backward compatible

### API Stability Indicators

- ✅ **Stable**: API is stable and won't change
- ⚠️ **Experimental**: API may change in future versions
- 🚧 **Planned**: Feature is planned but not yet implemented
- ❌ **Deprecated**: API will be removed in future versions

## Quick Links

<div class="grid cards" markdown>

-   :material-gamepad:{ .lg .middle } __Game Class__

    ---

    Core game engine class

    [:octicons-arrow-right-24: View Documentation](game.md)

-   :material-window-maximize:{ .lg .middle } __Window Class__

    ---

    Window management (Coming Soon)

    [:octicons-arrow-right-24: View Documentation](window.md)

-   :material-image:{ .lg .middle } __Renderer Class__

    ---

    2D rendering system (Coming Soon)

    [:octicons-arrow-right-24: View Documentation](renderer.md)

-   :material-folder:{ .lg .middle } __AssetManager Class__

    ---

    Asset loading and management (Coming Soon)

    [:octicons-arrow-right-24: View Documentation](asset-manager.md)

</div>

## Contributing to API Documentation

When contributing code to TwoDEngine, please:

1. **Document all public APIs**: Use Doxygen comment style
2. **Include examples**: Add usage examples in comments
3. **Update this overview**: Add new classes to the tables above
4. **Generate docs**: Run Doxygen to verify formatting
5. **Test examples**: Ensure code examples compile and run

See the [Contributing Guide](../development/contributing.md) for more details.

## API Design Principles

TwoDEngine APIs follow these principles:

1. **Simplicity**: Easy to use for common cases
2. **Consistency**: Similar patterns across the API
3. **Safety**: Type-safe and error-resistant
4. **Performance**: Efficient by default
5. **Extensibility**: Easy to extend and customize

---

!!! tip "Doxygen Documentation"
    For the most up-to-date and detailed API documentation, generate the Doxygen docs using `doxygen Doxyfile` and browse the HTML output.
