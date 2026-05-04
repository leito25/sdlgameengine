# TwoDEngine Examples

This directory contains example applications that demonstrate how to use the TwoDEngine.

## Available Examples

### SimpleGame

A basic game example that demonstrates:
- Creating and rendering game objects
- Handling player input
- Basic enemy AI
- Collision detection
- Rendering text
- Playing sound effects
- Using ImGui for debug UI
- Using GLM for vector math

## Building the Examples

Each example can be built using the provided Makefile:

```bash
cd examples
mingw32-make SimpleGame
```

## Running the Examples

After building, you can run the examples directly:

```bash
cd examples
./SimpleGame
```

Or use the run target in the Makefile:

```bash
cd examples
mingw32-make run
```

## Required DLLs

To run the examples, you'll need to copy the required DLLs to the examples directory:

```bash
copy ..\bin\SDL2.dll .
copy ..\bin\SDL2_image.dll .
copy ..\bin\SDL2_ttf.dll .
copy ..\bin\SDL2_mixer.dll .
copy ..\bin\lua54.dll .
```

## Example Details

### SimpleGame

This example demonstrates a simple game with the following features:

- **Player Control**: Use arrow keys to move the player character
- **Enemy AI**: Enemies follow the player
- **Health System**: Player loses health when colliding with enemies
- **UI**: Health and score display using both SDL_ttf and ImGui
- **Game Loop**: Proper game loop with delta time calculation
- **Resource Management**: Loading and managing textures, fonts, and sounds

#### Code Structure

The example is structured with the following classes:

- **GameObject**: Base class for game objects with position, velocity, and rendering
- **Player**: Extends GameObject with player-specific functionality
- **Enemy**: Extends GameObject with enemy AI behavior

#### Learning Points

- How to initialize SDL2 and its extensions
- How to create and manage game objects
- How to handle input and update game state
- How to render textures and text
- How to detect collisions
- How to integrate ImGui for debug UI
- How to use GLM for vector operations

## Creating Your Own Examples

To create your own example:

1. Create a new .cpp file in the examples directory
2. Add your example to the EXAMPLES variable in the Makefile
3. Build your example with `mingw32-make your_example_name`

## Additional Resources

For more information on using TwoDEngine, refer to:
- [Main README](../README.md)
- [Technical Documentation](../TECHNICAL.md)
- [Quick Start Guide](../QUICKSTART.md)