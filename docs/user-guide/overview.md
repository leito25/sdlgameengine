# User Guide Overview

Welcome to the TwoDEngine User Guide! This comprehensive guide will help you master all aspects of game development with TwoDEngine.

## What You'll Learn

This guide covers everything from basic concepts to advanced techniques for creating 2D games with TwoDEngine.

## Guide Structure

### 🎯 Core Concepts

Learn the fundamental concepts and architecture of TwoDEngine:

- **Game Loop**: Understanding the main game loop pattern
- **Entity-Component System**: Modern game architecture
- **Asset Management**: Loading and managing game resources
- **Scene Management**: Organizing game content

### 🎮 Game Development

Master the essential features for game development:

- **Window Management**: Creating and managing game windows
- **Input Handling**: Keyboard, mouse, and controller input
- **Graphics Rendering**: 2D sprite rendering and effects
- **Audio System**: Sound effects and background music
- **Physics**: Collision detection and response

### 🔧 Advanced Topics

Explore advanced features and optimization techniques:

- **Scripting**: Lua and Python integration
- **Performance**: Optimization and profiling
- **Debugging**: Tools and techniques
- **Networking**: Multiplayer support (planned)

## Quick Navigation

<div class="grid cards" markdown>

-   :material-window-maximize:{ .lg .middle } __Window & Rendering__

    ---

    Create windows and render graphics

    [:octicons-arrow-right-24: Learn More](window.md)

-   :material-gamepad-variant:{ .lg .middle } __Input Handling__

    ---

    Process user input from various devices

    [:octicons-arrow-right-24: Learn More](input.md)

-   :material-folder:{ .lg .middle } __Asset Management__

    ---

    Load and manage game assets

    [:octicons-arrow-right-24: Learn More](assets.md)

-   :material-script-text:{ .lg .middle } __Lua Scripting__

    ---

    Add scripting to your games

    [:octicons-arrow-right-24: Learn More](lua-scripting.md)

-   :material-language-python:{ .lg .middle } __Python Integration__

    ---

    Extend your game with Python

    [:octicons-arrow-right-24: Learn More](python-scripting.md)

-   :material-music:{ .lg .middle } __Audio System__

    ---

    Add sound effects and music

    [:octicons-arrow-right-24: Learn More](audio.md)

</div>

## Learning Path

### Beginner Path

1. **[Quick Start](../getting-started/quickstart.md)**: Set up your first project
2. **[Window Management](window.md)**: Create a game window
3. **[Input Handling](input.md)**: Handle keyboard and mouse
4. **[Asset Management](assets.md)**: Load images and fonts
5. **[Basic Rendering](rendering.md)**: Draw sprites to screen

### Intermediate Path

1. **[Animation System](animation.md)**: Animate sprites
2. **[Audio System](audio.md)**: Add sound effects
3. **[Collision Detection](collision.md)**: Implement physics
4. **[Lua Scripting](lua-scripting.md)**: Add game logic scripts
5. **[UI System](ui.md)**: Create game menus

### Advanced Path

1. **[Entity-Component System](ecs.md)**: Advanced architecture
2. **[Performance Optimization](optimization.md)**: Optimize your game
3. **[Python Integration](python-scripting.md)**: Extend with Python
4. **[Custom Shaders](shaders.md)**: Advanced graphics
5. **[Debugging Tools](debugging.md)**: Profile and debug

## Code Examples

Throughout this guide, you'll find practical code examples:

```cpp
// Example: Creating a simple game window
#include "Game.h"

int main(int argc, char* argv[])
{
    Game game;
    game.Initialize();
    game.Run();
    game.Destroy();
    return 0;
}
```

## Best Practices

Each section includes:

- ✅ **Recommended patterns**: What to do
- ❌ **Anti-patterns**: What to avoid
- 💡 **Tips**: Helpful hints and tricks
- ⚠️ **Warnings**: Common pitfalls

## Getting Help

If you get stuck:

1. **Search this guide**: Use the search bar at the top
2. **Check API Reference**: See [API Documentation](../api/overview.md)
3. **View Examples**: Browse [Example Projects](../examples/basic-game.md)
4. **Ask the Community**: Visit GitHub Discussions

## Contributing to the Guide

Found an error or want to improve the documentation?

- **Report Issues**: Open an issue on GitHub
- **Submit Improvements**: Create a pull request
- **Share Examples**: Contribute code examples

See the [Contributing Guide](../development/contributing.md) for details.

---

!!! tip "Interactive Learning"
    The best way to learn is by doing! Try the code examples as you read through the guide.

## Next Steps

Ready to dive in? Start with the [Quick Start Guide](../getting-started/quickstart.md) to create your first TwoDEngine project!
