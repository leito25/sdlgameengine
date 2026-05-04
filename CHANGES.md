# Changes Made to TwoDEngine

## Batch Files

1. **build_run_engine.bat**
   - Created a batch file to build and run the main engine
   - Added support for debug and release modes
   - Usage: `build_run_engine.bat [release]`

2. **build_run_sample_game.bat**
   - Created a batch file to build and run the sample game
   - Added support for debug and release modes
   - Usage: `build_run_sample_game.bat [release]`

3. **pack_sample_game.bat**
   - Created a batch file to package the sample game as a standalone application
   - Added support for both debug and release modes
   - Copies all necessary files to the dist directory (release) or dist-debug directory (debug)
   - Usage: `pack_sample_game.bat [debug]`

4. **build_run_python_game.bat**
  - Created a batch file to build and run the Python game example
  - Added support for debug and release modes
  - Usage: `build_run_python_game.bat [release]`

5. **pack_python_game.bat**
  - Created a batch file to package the Python game as a standalone application
  - Added support for both debug and release modes
  - Copies all necessary files including Python DLLs to the dist-python directory (release) or dist-python-debug directory (debug)
  - Usage: `pack_python_game.bat [debug]`

## VS Code Tasks

1. **Run Engine Tasks**
  - Updated to use the build_run_engine.bat script
  - Added support for debug and release modes

2. **Run Sample Game Tasks**
  - Updated to use the build_run_sample_game.bat script
  - Added support for debug and release modes

3. **Pack Sample Game Tasks**
  - Split into two separate tasks: Pack Sample Game (Debug) and Pack Sample Game (Release)
  - Updated to use the pack_sample_game.bat script with appropriate parameters
  - Debug task creates a distribution with debugging symbols in the dist-debug directory
  - Release task creates an optimized distribution in the dist directory

4. **Run Python Game Tasks**
  - Added tasks to build and run the Python game example
  - Added support for debug and release modes
  - Uses the build_run_python_game.bat script

5. **Pack Python Game Tasks**
  - Added tasks to package the Python game as a standalone application
  - Split into two separate tasks: Pack Python Game (Debug) and Pack Python Game (Release)
  - Uses the pack_python_game.bat script with appropriate parameters
  - Debug task creates a distribution with debugging symbols in the dist-python-debug directory
  - Release task creates an optimized distribution in the dist-python directory

## Documentation

1. **BATCH_FILES.md**
   - Created documentation for the batch files
   - Included usage instructions and parameters
   - Added documentation for Python-related batch files

2. **TASKS.md**
   - Created a task list for common operations
   - Included both batch file and VS Code task options

3. **README.md**
   - Updated to include information about the batch files
   - Updated the VS Code tasks section
   - Added information about Python scripting integration

4. **TECHNICAL.md**
   - Added detailed documentation about Python/pybind11 integration
   - Included code examples for Python initialization and usage
   - Added troubleshooting information for Python integration

5. **VSCODE_TASKS.md**
   - Updated to include Python game tasks
   - Added debugging configurations for the Python game
   - Added troubleshooting information for Python integration

## Testing

All batch files and VS Code tasks have been tested and are working correctly:

- The engine builds and runs in both debug and release modes
- The sample game builds and runs in both debug and release modes
- The packaging process creates a complete standalone distribution

## Benefits

These changes provide several benefits:

1. **Simplified Workflow**: Users can now build and run the engine and sample game with a single command
2. **Consistent Environment**: The batch files ensure that the correct compiler flags and paths are used
3. **Improved Documentation**: The new documentation files provide clear instructions for common tasks
4. **Flexible Options**: Support for both debug and release modes allows for different development needs
