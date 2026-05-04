# TwoDEngine Tasks

This document provides a list of common tasks for working with the TwoDEngine project.

## Getting Started

- [x] Download and set up SDL2 and its extensions
- [x] Integrate SDL2 with the existing project
- [x] Create a basic window with SDL2
- [x] Add ImGui integration
- [x] Add Lua scripting support
- [x] Create comprehensive documentation

## Building and Running

- [ ] Build and run the engine in debug mode
  ```
  build_run_engine.bat
  ```
  or use VS Code task: "Run Engine (Debug)"

- [ ] Build and run the engine in release mode
  ```
  build_run_engine.bat release
  ```
  or use VS Code task: "Run Engine (Release)"

- [ ] Build and run the sample game in debug mode
  ```
  build_run_sample_game.bat
  ```
  or use VS Code task: "Run Sample Game (Debug)"

- [ ] Build and run the sample game in release mode
  ```
  build_run_sample_game.bat release
  ```
  or use VS Code task: "Run Sample Game (Release)"

- [ ] Package the sample game as a standalone application (Release)
  ```
  pack_sample_game.bat
  ```
  or use VS Code task: "Pack Sample Game (Release)"

- [ ] Package the sample game as a standalone application (Debug)
  ```
  pack_sample_game.bat debug
  ```
  or use VS Code task: "Pack Sample Game (Debug)"

## Development Tasks

- [ ] Add a new game object class
  1. Create a new header file in `src/`
  2. Implement the class methods
  3. Include the header in your game file
  4. Create instances of the class

- [ ] Add a new asset
  1. Place the asset file in the appropriate directory under `assets/`
  2. Load the asset in your code using the appropriate SDL function
  3. Use the asset in your game

- [ ] Implement a new feature
  1. Plan the feature and identify the required components
  2. Implement the feature in the appropriate files
  3. Test the feature in the sample game
  4. Document the feature in the appropriate documentation file

## Debugging

- [ ] Debug the engine
  1. Set breakpoints in your code
  2. Use the "Debug Engine" task in VS Code
  3. Inspect variables and step through code

- [ ] Debug the sample game
  1. Set breakpoints in your code
  2. Use the "Debug Sample Game" task in VS Code
  3. Inspect variables and step through code

## Distribution

- [ ] Create a standalone distribution
  1. Run the `pack_sample_game.bat` script
  2. Verify that all required files are included in the `dist` directory
  3. Test the standalone application
  4. Distribute the contents of the `dist` directory

## Additional Resources

For more detailed information, refer to the following documentation:

- [README.md](README.md): Overview and basic usage
- [TECHNICAL.md](TECHNICAL.md): Detailed technical documentation
- [BATCH_FILES.md](BATCH_FILES.md): Documentation for utility batch files
- [VSCODE_TASKS.md](VSCODE_TASKS.md): VS Code tasks and debugging guide
